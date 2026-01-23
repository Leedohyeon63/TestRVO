// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RVOCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"

ARVOCharacter::ARVOCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

    AvoidanceRadius = 300.0f;
    AvoidanceWeight = 0.5f;

    UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
    if (MovementComponent)
    {
        // RVO 충돌 회피 알고리즘 활성화 여부
        MovementComponent->bUseRVOAvoidance = true;

        // AI가 다른 오브젝트를 감지하고 회피를 시작하는 반경
        MovementComponent->AvoidanceConsiderationRadius = AvoidanceRadius;

        // 캐릭터 회피 우선 순위(0.0f - 1.0f, 1에 가까울 수록 가중치 높음)
        MovementComponent->AvoidanceWeight = AvoidanceWeight;
    }
}

// Called when the game starts or when spawned
void ARVOCharacter::BeginPlay()
{
	Super::BeginPlay();
    AIController = Cast<AAIController>(GetController());

    if (AIController && TargetActor)
    {
        FTimerHandle DelayHandle;
        GetWorldTimerManager().SetTimer(DelayHandle, this, &ARVOCharacter::MoveToTarget, 2.0f, false);
    }
}

// Called to bind functionality to input
void ARVOCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARVOCharacter::MoveToTarget()
{
    if (!AIController || !TargetActor) return;

    AIController->MoveToActor(
        TargetActor,    // 목표 액터
        150.0f,         // 도착 판정 반경
        true,           // 목표 영역이 겹치면 도착으로 간주
        true,           // 경로 탐색 사용
        false           // 목적지를 네비게이션 메시에 투영(Projection) 하지 않음
    );

    UE_LOG(LogTemp, Display, TEXT("%s Moving to target: %s"), *GetName(), *TargetActor->GetName());
}

void ARVOCharacter::SetRVOAvoidanceEnabled(bool bEnabled)
{
}

