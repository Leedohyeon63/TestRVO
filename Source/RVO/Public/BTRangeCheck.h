// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTRangeCheck.generated.h"

class ATestDetourCrowdAIController;

UCLASS()
class RVO_API UBTRangeCheck : public UBTService
{
	GENERATED_BODY()

public:
	UBTRangeCheck();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere, Category = "AI|Optimization")
	float StickinessMultiplier = 1.2f;

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	struct FBlackboardKeySelector RangeKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	struct FBlackboardKeySelector AttackRangeKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	struct FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	struct FBlackboardKeySelector IsInRangeKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	struct FBlackboardKeySelector IsInAttackRangeKey;
};