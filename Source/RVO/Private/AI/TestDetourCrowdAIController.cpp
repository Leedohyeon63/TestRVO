// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TestDetourCrowdAIController.h"
#include "Character/RVOCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

ATestDetourCrowdAIController::ATestDetourCrowdAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

}

void ATestDetourCrowdAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BTAsset)
	{
		if (RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Log, TEXT("메인 BT 실행 성공"));
			SetUnitState(EUnitState::Move);

			ARVOCharacter* RVOChar = Cast<ARVOCharacter>(InPawn);
			if (RVOChar && RVOChar->SubBTAsset)
			{
				UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
				if (BTComp)
				{
					FGameplayTag CombatTag = FGameplayTag::RequestGameplayTag(TEXT("AI.State.Combat"));

					BTComp->SetDynamicSubtree(CombatTag, RVOChar->SubBTAsset);
					UE_LOG(LogTemp, Log, TEXT("%s : 다이나믹트리(%s)"),
						*InPawn->GetName(), *RVOChar->SubBTAsset->GetName());
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("FailRunBehaviorTree"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BTAssetNull"));
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
