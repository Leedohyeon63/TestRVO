// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTMove.h"
#include "AIController.h"
#include "Character/RVOCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTMove::UBTTMove()
{
	NodeName = "Move";
}

EBTNodeResult::Type UBTTMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!AIC) return EBTNodeResult::Failed;

    return EBTNodeResult::Succeeded;
}
