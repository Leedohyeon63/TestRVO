#include "Component/WaveComponent.h"
#include "TimerManager.h" // 타이머 사용을 위해 필요
#include "Engine/World.h"

UWaveComponent::UWaveComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWaveComponent::BeginPlay()
{
    Super::BeginPlay();
    StartAllWaves();

}

void UWaveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    UWorld* World = GetWorld();
    if (World)
    {
        for (FTimerHandle& Handle : WaveTimerHandles)
        {
            World->GetTimerManager().ClearTimer(Handle);
        }
    }
    WaveTimerHandles.Empty();
}



void UWaveComponent::StartAllWaves()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Log, TEXT("NoWorld"));
        return;
    }

    for (FTimerHandle& Handle : WaveTimerHandles)
    {
        World->GetTimerManager().ClearTimer(Handle);
    }
    WaveTimerHandles.Empty();

    for (const FWaveData& WaveData : Waves)
    {
        if (!WaveData.EnemyClass)
        {
            continue; 
        }

        FTimerHandle NewHandle;

        // 람다 캡처 [this, WaveData]
        World->GetTimerManager().SetTimer(
            NewHandle,
            [this, WaveData]()
            {
                this->SpawnEnemy(WaveData.EnemyClass);
            },
            WaveData.SpawnInterval,
            true 
        );

        WaveTimerHandles.Add(NewHandle);

    }
}


void UWaveComponent::SpawnEnemy(TSubclassOf<ARVOCharacter> EnemyClass)
{
    if (EnemyCount > 3)
    {
        return;
    }
    UWorld* World = GetWorld();
    if (!World || !EnemyClass)
    {
        UE_LOG(LogTemp, Log, TEXT("NoWorld"));
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    ARVOCharacter* SpawnedEnemy = World->SpawnActor<ARVOCharacter>(
        EnemyClass,
        GetComponentLocation(),
        GetComponentRotation(),
        SpawnParams
    );

    if (SpawnedEnemy)
    {
       // SpawnedEnemy->SetLifeSpan(10.0f);
        EnemyCount++;
        UE_LOG(LogTemp, Warning, TEXT("Enemy: %d"), EnemyCount);
        SpawnedEnemy->OnDestroyed.AddDynamic(this, &UWaveComponent::OnEnemyDestroyed);
    }
}

void UWaveComponent::OnEnemyDestroyed(AActor* DestroyedActor)
{
    if (DestroyedActor)
    {
        EnemyCount--;
        UE_LOG(LogTemp, Warning, TEXT("Enemy: %d"), EnemyCount);

    }
}





