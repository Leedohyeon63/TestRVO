// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FrontLineComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RVO_API UFrontLineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFrontLineComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 내 앞 이 거리 안에 아군이 있으면 속도를 줄임 (충돌 방지 거리)
	UPROPERTY(EditAnywhere, Category = "AI|FrontLine")
	float DetectionDistance = 120.0f;

	// 내 경로 좌우 폭 (이 값보다 좁게 위치한 아군만 '내 앞'에 있는 것으로 간주)
	// 보통 캡슐 반지름의 1.5~2배 정도로 설정
	UPROPERTY(EditAnywhere, Category = "AI|FrontLine")
	float PathWidthTolerance = 50.0f;

	// 앞이 막혔을 때 적용할 속도 비율 (0.1 = 10% 속도로 서행)
	UPROPERTY(EditAnywhere, Category = "AI|FrontLine")
	float SlowDownFactor = 0.15f;

private:
	float CachedMaxWalkSpeed = 0.0f;
	bool bIsMovementRestricted = false;

	float CheckInterval = 0.1f;
	float TimeSinceLastCheck = 0.0f;

	UPROPERTY()
	class ATestDetourCrowdAIController* OwnerController;

	UPROPERTY()
	class UUnitSubsystem* UnitSubsystem;

	UPROPERTY()
	class ACharacter* OwnerCharacter;

	UPROPERTY()
	class UCharacterMovementComponent* OwnerMovement;
};