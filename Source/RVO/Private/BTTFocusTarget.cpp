// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTFocusTarget.h"
#include "AIController.h"
#include "Character/RVOCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTFocusTarget::UBTTFocusTarget()
{
	NodeName = "Focus";
    bNotifyTick = true;

}

EBTNodeResult::Type UBTTFocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    return EBTNodeResult::InProgress;
}

void UBTTFocusTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!AIC || !AIC->GetPawn())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    ARVOCharacter* Unit = Cast<ARVOCharacter>(AIC->GetPawn());
    if (!Unit)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName);
    AActor* TargetActor = Cast<AActor>(TargetObject);

    if (!TargetActor)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (Unit->FocusTarget(TargetActor, DeltaSeconds, TurnSpeed))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}


