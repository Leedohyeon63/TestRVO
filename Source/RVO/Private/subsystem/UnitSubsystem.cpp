// Fill out your copyright notice in the Description page of Project Settings.


#include "subsystem/UnitSubsystem.h"
#include "Tag/UnitTag.h"

void UUnitSubsystem::RegisterUnit(AActor* Unit, FGameplayTag TeamTag)
{
    if (!Unit || !TeamTag.IsValid())
    {
        return;
    }

    FUnitList& UnitList = TeamUnitsMap.FindOrAdd(TeamTag);
    UnitList.Units.AddUnique(Unit);
}

void UUnitSubsystem::UnregisterUnit(AActor* Unit, FGameplayTag TeamTag)
{
    if (!Unit || !TeamTag.IsValid())
    {
        return;
    }

    if (FUnitList* UnitList = TeamUnitsMap.Find(TeamTag))
    {
        UnitList->Units.Remove(Unit);

        if (UnitList->Units.Num() == 0)
        {
            TeamUnitsMap.Remove(TeamTag);
        }
    }
}

const TArray<TWeakObjectPtr<AActor>>& UUnitSubsystem::GetUnitsByTeam(FGameplayTag TeamTag) const
{
    if (const FUnitList* UnitList = TeamUnitsMap.Find(TeamTag))
    {
        return UnitList->Units;
    }
    return EmptyArray;
}
