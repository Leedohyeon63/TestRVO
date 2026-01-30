// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DetourCrowdAIController.h"
#include "TestDetourCrowdAIController.generated.h"

/**
 * 
 */
UCLASS()
class RVO_API ATestDetourCrowdAIController : public ADetourCrowdAIController
{
	GENERATED_BODY()
public:
	ATestDetourCrowdAIController();

protected:

	//빙의(Possess)될 때 호출됨.(유닛 스폰 시점)
	virtual void OnPossess(APawn* InPawn) override;

	//빙의 해제될 때(유닛 사망, 풀반납)
	virtual void OnUnPossess() override;

public:

	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	//블랙보드 컴포넌트 (데이터 저장소)
	UPROPERTY(VisibleAnywhere, Category = "AI")
	TObjectPtr<class UBlackboardComponent> BlackboardComp;

	//현재 빙의한 유닛의 팀 정보 캐싱
	FGenericTeamId CachedTeamId;
};
