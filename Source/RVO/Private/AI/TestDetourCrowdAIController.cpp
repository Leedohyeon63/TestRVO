// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TestDetourCrowdAIController.h"
#include "Character/RVOCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h" // RVO 설정용

ATestDetourCrowdAIController::ATestDetourCrowdAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

}

void ATestDetourCrowdAIController::OnPossess(APawn* InPawn)
{
}

void ATestDetourCrowdAIController::OnUnPossess()
{
}

FGenericTeamId ATestDetourCrowdAIController::GetGenericTeamId() const
{
	return FGenericTeamId();
}
