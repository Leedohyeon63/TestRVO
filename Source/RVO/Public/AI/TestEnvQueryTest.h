// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "TestEnvQueryTest.generated.h"

/**
 * 
 */
UCLASS()
class RVO_API UTestEnvQueryTest : public UEnvQueryTest
{
	GENERATED_BODY()
public:
    UTestEnvQueryTest();

    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

    UPROPERTY(EditDefaultsOnly, Category = "Behind")
    TSubclassOf<UEnvQueryContext> ComparisonContext;
};
