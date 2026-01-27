// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Character/RVOCharacter.h"
#include "WaveComponent.generated.h"

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARVOCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnInterval = 1.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RVO_API UWaveComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UWaveComponent();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WaveSystem")
	TArray<FWaveData> Waves;

protected:
	TArray<FTimerHandle> WaveTimerHandles;

	UFUNCTION(BlueprintCallable)
	void StartAllWaves();

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);

	void SpawnEnemy(TSubclassOf<ARVOCharacter> EnemyClass);

public:
	int32 EnemyCount = 0;
};
