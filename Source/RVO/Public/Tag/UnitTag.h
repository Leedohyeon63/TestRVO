// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 * 
 */
class RVO_API UnitTag
{
};

namespace UnitTags
{
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_Tier_Normal);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_Tier_Rare);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_Tier_Epic);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_Element_Fire);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_Element_Water);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_Element_Electric);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_Branch_Melee);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_Branch_Ranged);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_Branch_Mage);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_Branch_Tank);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_FriendorFoe_Friend);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unit_FriendorFoe_Foe);
}