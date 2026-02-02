// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TestEnvQueryTest.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

UTestEnvQueryTest::UTestEnvQueryTest()
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
    ComparisonContext = UEnvQueryContext_Querier::StaticClass();
}

void UTestEnvQueryTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
    UObject* QueryOwner = QueryInstance.Owner.Get();
    if (!QueryOwner) return;

    TArray<AActor*> ContextActors;
    if (!QueryInstance.PrepareContext(ComparisonContext, ContextActors)) return;
    for (AActor* TargetActor : ContextActors)
    {
        FVector TargetLoc3D = TargetActor->GetActorLocation();
        FVector2D TargetLoc2D(TargetLoc3D.X, TargetLoc3D.Y);

        FVector TargetFwd3D = TargetActor->GetActorForwardVector();
        FVector2D TargetFwd2D(TargetFwd3D.X, TargetFwd3D.Y);

        for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
        {
            FVector ItemLoc3D = GetItemLocation(QueryInstance, It.GetIndex());
            FVector2D ItemLoc2D(ItemLoc3D.X, ItemLoc3D.Y);

            FVector2D DirToItem = ItemLoc2D - TargetLoc2D;

            float DotVal = FVector2D::DotProduct(TargetFwd2D, DirToItem);

            if (DotVal < 0.0f)
            {
                It.SetScore(TestPurpose, FilterType, 1.0f, 0.0f, 1.0f);
            }
            else
            {
                It.SetScore(TestPurpose, FilterType, 0.0f, 0.0f, 1.0f);
            }
        }
    }
}
