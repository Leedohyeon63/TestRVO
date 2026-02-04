// Fill out your copyright notice in the Description page of Project Settings.


#include "BTRangeCheck.h"
#include "AIController.h"
#include "Tag/UnitTag.h"
#include "AI/TestDetourCrowdAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameplayTagAssetInterface.h"
#include "Kismet/GameplayStatics.h"

UBTRangeCheck::UBTRangeCheck()
{
	NodeName = "RangeCheck";
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBTRangeCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ATestDetourCrowdAIController* AIC = Cast<ATestDetourCrowdAIController>(OwnerComp.GetAIOwner());
    APawn* ControllingPawn = AIC ? AIC->GetPawn() : nullptr;
    if (!ControllingPawn)
    {
        return;
    }

    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard)
    {
        return;
    }

    float Range = Blackboard->GetValueAsFloat(RangeKey.SelectedKeyName);

    // 1. 내(Self) 진영 확인
    IGameplayTagAssetInterface* SelfInterface = Cast<IGameplayTagAssetInterface>(ControllingPawn);
    if (!SelfInterface)
    {
        return;
    }

    // 내가 아군이면 적군 태그를, 내가 적군이면 아군 태그를 타겟으로 설정합니다.
    FGameplayTag EnemyTag = SelfInterface->HasMatchingGameplayTag(UnitTags::Unit_FriendorFoe_Friend)
        ? UnitTags::Unit_FriendorFoe_Foe
        : UnitTags::Unit_FriendorFoe_Friend;

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UGameplayTagAssetInterface::StaticClass(), FoundActors);

    AActor* ClosestTarget = nullptr;
    float MinDistance = Range;
    bool bInRange = false;

    for (AActor* Actor : FoundActors)
    {
        if (Actor == ControllingPawn)
        {
            continue;
        }

        IGameplayTagAssetInterface* TargetInterface = Cast<IGameplayTagAssetInterface>(Actor);
        // 2. 타겟이 나의 반대 진영 태그를 가지고 있는지 확인
        if (TargetInterface && TargetInterface->HasMatchingGameplayTag(EnemyTag))
        {
            float Distance = ControllingPawn->GetDistanceTo(Actor);
            if (Distance <= MinDistance)
            {
                MinDistance = Distance;
                ClosestTarget = Actor;
                bInRange = true;
            }
        }
    }

    // 블랙보드 및 AI 상태 업데이트
    Blackboard->SetValueAsObject(TargetActorKey.SelectedKeyName, ClosestTarget);
    Blackboard->SetValueAsBool(IsInRangeKey.SelectedKeyName, bInRange);

    if (AIC)
    {
        // 적을 발견하면 Combat, 없으면 Move 상태로 변경
        AIC->SetUnitState(bInRange ? EUnitState::Combat : EUnitState::Move);
    }
}