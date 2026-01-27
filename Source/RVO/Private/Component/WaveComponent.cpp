

#include "Component/WaveComponent.h"

UWaveComponent::UWaveComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UWaveComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UWaveComponent::SpawnEnemiesDelayed(int32 WaveIndex)
{
}


