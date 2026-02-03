// Fill out your copyright notice in the Description page of Project Settings.


#include "BTRangeCheck.h"
#include "AIController.h"
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

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (!ControllingPawn) return;

    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard) return;

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UGameplayTagAssetInterface::StaticClass(), FoundActors);

    AActor* ClosestTarget = nullptr;
    float MinDistance = SearchRange;
    bool bInRange = false;

    for (AActor* Actor : FoundActors)
    {
        if (Actor == ControllingPawn) continue;

        IGameplayTagAssetInterface* TagInterface = Cast<IGameplayTagAssetInterface>(Actor);
        if (TagInterface && TagInterface->HasMatchingGameplayTag(TargetTag))
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

    Blackboard->SetValueAsObject(TargetActorKey.SelectedKeyName, ClosestTarget);
    Blackboard->SetValueAsBool(IsInRangeKey.SelectedKeyName, bInRange);
}