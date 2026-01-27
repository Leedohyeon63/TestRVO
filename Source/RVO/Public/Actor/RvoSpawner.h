// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RvoSpawner.generated.h"

UCLASS()
class RVO_API ARvoSpawner : public AActor
{
	GENERATED_BODY()
public:
    // Sets default values for this actor's properties
    ARvoSpawner();

protected:
    virtual void BeginPlay() override;

    void SpawnActorWave();

    FTimerHandle SpawnTimerHandle;

public:
    UPROPERTY(EditAnywhere, Category = "Spawn|Enemy")
    TSubclassOf<AActor> SpawnActor;


    UPROPERTY(EditAnywhere, Category = "Spawn|time")
    float SpawnInterval_LV1 = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Spawn|time")
    float SpawnInterval_LV2 = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Spawn|time")
    float SpawnInterval_LV3 = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Spawn|time")
    float SpawnInterval_LV4 = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Spawn|time")
    float SpawnInterval_LV5 = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    FVector SpawnRange = FVector(1000.0f, 1000.0f, 0.0f);

};
