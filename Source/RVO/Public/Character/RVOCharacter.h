// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NativeGameplayTags.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "RVOCharacter.generated.h"

UCLASS()
class RVO_API ARVOCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARVOCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    UFUNCTION(BlueprintCallable, Category = "AI Movement")
    void MoveToTarget();

    // RVO 회피 활성화/비활성화
    UFUNCTION(BlueprintCallable, Category = "RVO")
    void SetRVOAvoidanceEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "RVO")
    void SetAttackTarget(AActor* InTargetActor);

public:
    // 이동할 타겟 액터
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Movement")
    TObjectPtr<AActor> TargetActor = nullptr;

    // RVO 회피 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RVO")
    float AvoidanceRadius;

    // RVO 계급 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RVO")
    float AvoidanceWeight;

private:
    // AI 컨트롤러 캐싱
    class AAIController* AIController;

};
