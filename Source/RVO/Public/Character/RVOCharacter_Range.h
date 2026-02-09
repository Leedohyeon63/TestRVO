// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RVOCharacter.h"
#include "RVOCharacter_Range.generated.h"

/**
 * 
 */
UCLASS()
class RVO_API ARVOCharacter_Range : public ARVOCharacter
{
	GENERATED_BODY()
public:
	ARVOCharacter_Range();
	virtual void PostInitProperties() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AActor> projectile = nullptr;

protected:
	virtual void TestAttack() override;
};
