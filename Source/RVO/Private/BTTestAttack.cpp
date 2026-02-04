// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTestAttack.h"
#include "AIController.h"
#include "Character/RVOCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTestAttack::UBTTestAttack()
{
	//노드에 표시할 이름 (다른 태스크도 같음 이름만 다름)
	NodeName = "TestAttack";
}

EBTNodeResult::Type UBTTestAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!AIC) return EBTNodeResult::Failed;

    ARVOCharacter* Unit = Cast<ARVOCharacter>(AIC->GetPawn());
    if (!Unit) return EBTNodeResult::Failed;

    Unit->TestAttack();

    return EBTNodeResult::Succeeded;
}
