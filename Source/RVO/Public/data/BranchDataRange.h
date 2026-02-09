// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "BranchDataRange.generated.h"

/**
 * 
 */
UCLASS()
class RVO_API UBranchDataRange : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
	FGameplayTag SideTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
	FGameplayTag BranchTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<class UBehaviorTree> SubBTAsset;
};
