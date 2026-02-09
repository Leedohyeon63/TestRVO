// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RVOCharacter.h"
#include "RVOCharacter_Mage.generated.h"

/**
 * 
 */
UCLASS()
class RVO_API ARVOCharacter_Mage : public ARVOCharacter
{
	GENERATED_BODY()
public:
	ARVOCharacter_Mage();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AActor> Barrier = nullptr;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* GuardMontage = nullptr;

protected:
	virtual void TestAttack() override;
};
