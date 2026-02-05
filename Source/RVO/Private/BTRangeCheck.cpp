// Fill out your copyright notice in the Description page of Project Settings.


#include "BTRangeCheck.h"
#include "AIController.h"
#include "Tag/UnitTag.h"
#include "AI/TestDetourCrowdAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameplayTagAssetInterface.h"
#include "Kismet/GameplayStatics.h"
#include "subsystem/UnitSubsystem.h"

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

    APawn* ControllPawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;
    if (!ControllPawn)
    {
        return;
    }

    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard)
    {
        return;
    }

    UUnitSubsystem* UnitSubSystem = GetWorld()->GetSubsystem<UUnitSubsystem>();
    if (!UnitSubSystem)
    {
        return;
    }

    float Range = Blackboard->GetValueAsFloat(RangeKey.SelectedKeyName);
    float RangeSq = Range * Range;

    float AttackRange = Blackboard->GetValueAsFloat(AttackRangeKey.SelectedKeyName);
    float AttackRangeSq = AttackRange * AttackRange;

    IGameplayTagAssetInterface* UnitInterface = Cast<IGameplayTagAssetInterface>(ControllPawn);
    if (!UnitInterface)
    {
        return;
    }

    FGameplayTag EnemyTag = UnitInterface->
        HasMatchingGameplayTag(UnitTags::Unit_FriendorFoe_Friend)
        ? UnitTags::Unit_FriendorFoe_Foe
        : UnitTags::Unit_FriendorFoe_Friend;

    const TArray<TWeakObjectPtr<AActor>>& EnemyList = UnitSubSystem->GetUnitsByTeam(EnemyTag);

    AActor* ClosestTarget = nullptr;
    float MinDistSq = RangeSq;
    bool bInRange = false;
    bool bInAttackRange = false;

    FVector MyLocation = ControllPawn->GetActorLocation();

    for (const TWeakObjectPtr<AActor>& EnemyPtr : EnemyList)
    {
        AActor* Enemy = EnemyPtr.Get();
        if (!Enemy) continue;

        float DistSq = FVector::DistSquared(MyLocation, Enemy->GetActorLocation());

        if (DistSq <= MinDistSq)
        {
            MinDistSq = DistSq;
            ClosestTarget = Enemy;
            bInRange = true;
        }
    }

    if (bInRange && ClosestTarget)
    {
        if (MinDistSq <= AttackRangeSq)
        {
            bInAttackRange = true;
        }
    }

    Blackboard->SetValueAsObject(TargetActorKey.SelectedKeyName, ClosestTarget);
    Blackboard->SetValueAsBool(IsInRangeKey.SelectedKeyName, bInRange);
    Blackboard->SetValueAsBool(IsInAttackRangeKey.SelectedKeyName, bInAttackRange);

    if (AIC)
    {
        // 적을 발견하면 Combat, 없으면 Move 상태로 변경
        AIC->SetUnitState(bInRange ? EUnitState::Combat : EUnitState::Move);
    }
}