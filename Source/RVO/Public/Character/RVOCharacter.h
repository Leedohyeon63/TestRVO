// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NativeGameplayTags.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "RVOCharacter.generated.h"

UCLASS()
class RVO_API ARVOCharacter : public ACharacter, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	ARVOCharacter();
protected:
    void SetMoveSpeed();
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    UFUNCTION(BlueprintCallable, Category = "AI Movement")
    bool FocusTarget(AActor* InTargetActor, float DeltaTime, float TurnSpeed);

    //// RVO 회피 활성화/비활성화
    //UFUNCTION(BlueprintCallable, Category = "RVO")
    //void SetRVOAvoidanceEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "RVO")
    void SetAttackTarget(AActor* InTargetActor);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void TestAttack();

    UPROPERTY(EditAnywhere, Category = "AI")
    FGameplayTag UnitTag;

    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override
    {
        TagContainer.AddTag(UnitTag);
    }

public:
    // 이동할 타겟 액터
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Movement")
    TObjectPtr<AActor> TargetActor = nullptr;

    //// RVO 회피 설정
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RVO")
    //float AvoidanceRadius;

    //// RVO 계급 설정
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RVO")
    //float AvoidanceWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TObjectPtr<class UBehaviorTree> SubBTAsset;

    UPROPERTY(EditAnywhere, Category = "Combat")
    UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float DetectRange = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float AttackRange = 250.0f;
private:
    // AI 컨트롤러 캐싱
    class AAIController* AIController = nullptr;

};
