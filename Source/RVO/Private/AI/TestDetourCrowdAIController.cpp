// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TestDetourCrowdAIController.h"
#include "Character/RVOCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"

ATestDetourCrowdAIController::ATestDetourCrowdAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

}

void ATestDetourCrowdAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn); // Super를 먼저 호출하여 내부 시스템을 초기화합니다.

	UE_LOG(LogTemp, Warning, TEXT("OnPossess Called for: %s"), *InPawn->GetName());

	if (BTAsset)
	{
		if (RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Log, TEXT("BT실행 성공"));
			SetUnitState(EUnitState::Move);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("RunBehaviorTree 실패!"));
		}
	}
	else
	{
		// 십중팔구 이 로그가 찍힐 것입니다. 블루프린트에서 할당을 확인하세요.
		UE_LOG(LogTemp, Error, TEXT("BTAsset이 Null입니다! 블루프린트 할당을 확인하세요."));
	}
}

void ATestDetourCrowdAIController::OnUnPossess()
{
	if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent))
	{
		BTComp->StopTree(EBTStopMode::Safe);
	}

	Super::OnUnPossess();
}

FGenericTeamId ATestDetourCrowdAIController::GetGenericTeamId() const
{
	return FGenericTeamId();
}

void ATestDetourCrowdAIController::SetUnitState(EUnitState NewState)
{
	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(NewState));

		if (NewState == EUnitState::Dead)
		{
			// 필요한 경우 여기서 BrainComponent 중지 가능
		}
	}
}
