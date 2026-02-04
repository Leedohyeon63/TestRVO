// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SetSpeed.h"
#include "AIController.h"
#include "Character/RVOCharacter.h"

UBTT_SetSpeed::UBTT_SetSpeed()
{
	NodeName = "SetSpeed";
}

EBTNodeResult::Type UBTT_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!AIC) return EBTNodeResult::Failed;
    return EBTNodeResult::Succeeded;
}
