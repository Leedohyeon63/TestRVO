// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTFocusTarget.generated.h"

/**
 * 
 */
UCLASS()
class RVO_API UBTTFocusTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTFocusTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
public:
	UPROPERTY(EditAnywhere, Category = "AI")
	float TurnSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = "AI")
	struct FBlackboardKeySelector TargetKey;
};
