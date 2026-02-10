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
    // ������ ������ �� ȣ���Ͽ� ���
    void RegisterUnit(AActor* Unit, FGameplayTag TeamTag);

    // ������ ���ŵ� �� ȣ���Ͽ� ����
    void UnregisterUnit(AActor* Unit, FGameplayTag TeamTag);

    // Ư�� ������ ���� ����Ʈ�� ��ȯ
    const TArray<TWeakObjectPtr<AActor>>& GetUnitsByTeam(FGameplayTag TeamTag) const;

private:
    // Friend/Foe �±׺��� ���͵��� ����
    UPROPERTY()
    TMap<FGameplayTag, FUnitList> TeamUnitsMap;

    // �� �迭 ��ȯ�� (���� ����)
    TArray<TWeakObjectPtr<AActor>> EmptyArray;
};
