// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/FrontLineComponent.h"
#include "AI/TestDetourCrowdAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "subsystem/UnitSubsystem.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Tag/UnitTag.h" 
#include "GameplayTagAssetInterface.h"
#include "Components/CapsuleComponent.h"

UFrontLineComponent::UFrontLineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFrontLineComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		OwnerController = Cast<ATestDetourCrowdAIController>(OwnerCharacter->GetController());
		OwnerMovement = OwnerCharacter->GetCharacterMovement();

		if (OwnerMovement)
		{
			CachedMaxWalkSpeed = OwnerMovement->MaxWalkSpeed;
		}
	}

	if (GetWorld())
	{
		UnitSubsystem = GetWorld()->GetSubsystem<UUnitSubsystem>();
	}
}

void UFrontLineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 1. 필수 컴포넌트 체크
	if (!OwnerController || !OwnerCharacter || !UnitSubsystem || !OwnerMovement)
	{
		return;
	}

	// 2. 틱 최적화
	TimeSinceLastCheck += DeltaTime;
	if (TimeSinceLastCheck < CheckInterval) return;
	TimeSinceLastCheck = 0.0f;

	// 3. 전투 상태 체크 (전투 중일 때만 동작)
	UBlackboardComponent* BB = OwnerController->GetBlackboardComponent();
	if (!BB) return;

	// State Enum 값 확인 (1 == Combat 라고 가정)
	uint8 CurrentState = BB->GetValueAsEnum(TEXT("State"));
	if (CurrentState != 1)
	{
		// 전투 상태가 풀리면 속도 복구
		if (bIsMovementRestricted)
		{
			OwnerMovement->MaxWalkSpeed = CachedMaxWalkSpeed;
			bIsMovementRestricted = false;
		}
		return;
	}

	// 4. 타겟 방향 확인
	AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TEXT("TargetActor")));
	if (!TargetActor)
	{
		if (bIsMovementRestricted)
		{
			OwnerMovement->MaxWalkSpeed = CachedMaxWalkSpeed;
			bIsMovementRestricted = false;
		}
		return;
	}

	// 5. 아군 리스트 가져오기
	IGameplayTagAssetInterface* TagInterface = Cast<IGameplayTagAssetInterface>(OwnerCharacter);
	if (!TagInterface) return;

	bool bIsMyTeamFriend = TagInterface->HasMatchingGameplayTag(UnitTags::Unit_FriendorFoe_Friend);
	FGameplayTag MyTeamTag = bIsMyTeamFriend ? UnitTags::Unit_FriendorFoe_Friend : UnitTags::Unit_FriendorFoe_Foe;

	const TArray<TWeakObjectPtr<AActor>>& AllyList = UnitSubsystem->GetUnitsByTeam(MyTeamTag);

	// 6. "내 앞" 검사 로직
	FVector MyLoc = OwnerCharacter->GetActorLocation();
	FVector TargetLoc = TargetActor->GetActorLocation();

	// 내가 가고자 하는 방향 (타겟 방향)
	FVector ForwardDir = (TargetLoc - MyLoc).GetSafeNormal2D();

	bool bIsBlockedByAlly = false;
	float MyCapsuleRadius = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();

	// 너무 먼 거리의 아군은 미리 거르기 위한 제곱 거리 (최적화용)
	float SearchLimitSq = FMath::Square(DetectionDistance * 2.0f);

	for (const TWeakObjectPtr<AActor>& AllyPtr : AllyList)
	{
		AActor* Ally = AllyPtr.Get();
		if (!Ally || Ally == OwnerCharacter) continue;

		FVector AllyLoc = Ally->GetActorLocation();

		// 1차 필터: 너무 멀리 있는 아군은 연산 제외
		if (FVector::DistSquaredXY(MyLoc, AllyLoc) > SearchLimitSq) continue;

		// 상대방 위치 벡터 (나 -> 상대)
		FVector ToAlly = AllyLoc - MyLoc;

		// 전방 거리 (ForwardDir 기준 얼마나 앞에 있는가)
		float ForwardDist = FVector::DotProduct(ToAlly, ForwardDir);

		// [조건 1] 내 뒤에 있는 아군은 무시 (ForwardDist <= 0)
		// [조건 2] 너무 멀리 있는 앞 아군도 무시 (ForwardDist > DetectionDistance)
		if (ForwardDist <= 0.0f || ForwardDist > DetectionDistance) continue;

		// 측면 거리 계산 (내 진행 경로를 가로막고 있는가?)
		// 공식: (ToAlly - (ForwardDir * ForwardDist))의 길이
		FVector SideVector = ToAlly - (ForwardDir * ForwardDist);
		float SideDistSq = SideVector.SizeSquared2D();

		// 상대방의 크기도 고려 (상대방 캡슐 반지름)
		float AllyRadius = 40.0f; // 기본값
		if (UCapsuleComponent* AllyCapsule = Ally->FindComponentByClass<UCapsuleComponent>())
		{
			AllyRadius = AllyCapsule->GetScaledCapsuleRadius();
		}

		// [조건 3] 내 경로 폭(PathWidthTolerance) + 상대방 크기 안쪽으로 들어와 있는가?
		// 즉, 내가 그대로 직진하면 부딪힐 위치에 있는가?
		float CollisionThreshold = PathWidthTolerance + AllyRadius;
		if (SideDistSq < (CollisionThreshold * CollisionThreshold))
		{
			bIsBlockedByAlly = true;
			break; // 한 명이라도 막고 있으면 더 볼 것 없음
		}
	}

	// 7. 속도 제어
	if (bIsBlockedByAlly)
	{
		if (!bIsMovementRestricted)
		{
			// 앞이 막힘 -> 서행
			OwnerMovement->MaxWalkSpeed = CachedMaxWalkSpeed * SlowDownFactor;
			bIsMovementRestricted = true;
		}
	}
	else
	{
		if (bIsMovementRestricted)
		{
			// 앞이 뚫림 -> 정상 속도 복구
			OwnerMovement->MaxWalkSpeed = CachedMaxWalkSpeed;
			bIsMovementRestricted = false;
		}
	}
}