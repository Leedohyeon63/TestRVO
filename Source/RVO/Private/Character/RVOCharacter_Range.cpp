#include "Character/RVOCharacter_Range.h"
#include "Tag/UnitTag.h"

ARVOCharacter_Range::ARVOCharacter_Range()
{
}

void ARVOCharacter_Range::PostInitProperties()
{
    Super::PostInitProperties();
    BranchTag = UnitTags::Unit_Branch_Ranged; // <- 이 코드는 제거
}
void ARVOCharacter_Range::TestAttack()
{
    Super::TestAttack(); 
    UE_LOG(LogTemp, Warning, TEXT("Range Unit Attacks!"));

}