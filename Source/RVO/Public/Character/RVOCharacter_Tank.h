// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RVOCharacter.h"
#include "RVOCharacter_Tank.generated.h"



UCLASS()
class RVO_API ARVOCharacter_Tank : public ARVOCharacter
{
	GENERATED_BODY()

public:
	ARVOCharacter_Tank();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AActor> Barrier = nullptr;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* GuardMontage = nullptr;

protected:
	virtual void TestAttack() override;
};
