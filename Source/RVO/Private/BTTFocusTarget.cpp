// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTFocusTarget.h"
#include "AIController.h"
#include "Character/RVOCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTFocusTarget::UBTTFocusTarget()
{
	NodeName = "Move";

}

EBTNodeResult::Type UBTTFocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

void UBTTFocusTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIC = OwnerComp.GetAIOwner();
    ARVOCharacter* Unit = Cast<ARVOCharacter>(AIC ? AIC->GetPawn() : nullptr);

    UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName);
    AActor* TargetActor = Cast<AActor>(TargetObject);

    Unit->FocusTarget(TargetActor, DeltaSeconds, TurnSpeed);

    if (Unit->FocusTarget(TargetActor, DeltaSeconds, TurnSpeed))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}


