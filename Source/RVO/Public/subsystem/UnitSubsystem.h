// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "UnitSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FUnitList
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<TWeakObjectPtr<AActor>> Units;
};

UCLASS()
class RVO_API UUnitSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
    // 유닛이 스폰될 때 호출하여 등록
    void RegisterUnit(AActor* Unit, FGameplayTag TeamTag);

    // 유닛이 제거될 때 호출하여 해제
    void UnregisterUnit(AActor* Unit, FGameplayTag TeamTag);

    // 특정 진영의 유닛 리스트를 반환
    const TArray<TWeakObjectPtr<AActor>>& GetUnitsByTeam(FGameplayTag TeamTag) const;

private:
    // Friend/Foe 태그별로 액터들을 관리
    UPROPERTY()
    TMap<FGameplayTag, FUnitList> TeamUnitsMap;

    // 빈 배열 반환용 (에러 방지)
    TArray<TWeakObjectPtr<AActor>> EmptyArray;
};
