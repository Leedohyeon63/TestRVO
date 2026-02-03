// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enum/Enumclass.h" 
#include "BTT_SetSpeed.generated.h"

/**
 * 
 */
UCLASS()
class RVO_API UBTT_SetSpeed : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_SetSpeed();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EUnitState State;
};
