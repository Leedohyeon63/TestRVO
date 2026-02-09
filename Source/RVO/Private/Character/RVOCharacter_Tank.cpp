// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RVOCharacter_Tank.h"

ARVOCharacter_Tank::ARVOCharacter_Tank()
{
}

void ARVOCharacter_Tank::TestAttack()
{
	Super::TestAttack();
	UE_LOG(LogTemp, Warning, TEXT("탱커공격"));
}
