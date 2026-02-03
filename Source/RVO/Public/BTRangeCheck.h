// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTRangeCheck.generated.h"

/**
 * 
 */
UCLASS()
class RVO_API UBTRangeCheck : public UBTService
{
	GENERATED_BODY()
public:
    UBTRangeCheck();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
    UPROPERTY(EditAnywhere, Category = "AI")
    float SearchRange = 1000.0f;

    // 수정: 일반 Tag 대신 Gameplay Tag 사용
    UPROPERTY(EditAnywhere, Category = "AI")
    FGameplayTag TargetTag;

    UPROPERTY(EditAnywhere, Category = "AI")
    struct FBlackboardKeySelector TargetActorKey;

    UPROPERTY(EditAnywhere, Category = "AI")
    struct FBlackboardKeySelector IsInRangeKey;
};
