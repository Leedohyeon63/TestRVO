// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Character/RVOCharacter.h"
#include "WaveComponent.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARVOCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime = 1.0f;
};

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (TitleProperty = "EnemyClass"))
	TArray<FSpawnInfo> SpawnList;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RVO_API UWaveComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UWaveComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WaveSystem")
	TArray<FWaveData> Waves;
protected:
	//웨이브에 있는 몬스터를 스폰하는 함수
	void SpawnEnemiesDelayed(int32 WaveIndex);
};
