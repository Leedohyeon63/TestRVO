// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RvoSpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
ARvoSpawner::ARvoSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ARvoSpawner::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(
        SpawnTimerHandle,
        this,
        &ARvoSpawner::SpawnActorWave,
        SpawnInterval_LV1,
        true
    );
}

void ARvoSpawner::SpawnActorWave()
{
    if (!SpawnActorWave) return;

    FVector RandomLocation = GetActorLocation() + FVector(
        UKismetMathLibrary::RandomFloatInRange(-SpawnRange.X, SpawnRange.X),
        UKismetMathLibrary::RandomFloatInRange(-SpawnRange.Y, SpawnRange.Y),
        100.0f
    );

    FRotator RandomRotation = FRotator(0.0f, UKismetMathLibrary::RandomFloatInRange(0.0f, 360.0f), 0.0f);

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AActor* SpawnedItem = GetWorld()->SpawnActor<AActor>(SpawnActor, RandomLocation, RandomRotation, SpawnParams);
}


