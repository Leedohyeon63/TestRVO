#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "Enum/Enumclass.h" 
#include "BTDecorator_CheckState.generated.h"

UCLASS()
class RVO_API UBTDecorator_CheckState : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckState();

protected:
	// 조건이 맞는지 판단하는 핵심 함수입니다.
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
	// 에디터에서 비교하고 싶은 상태를 선택합니다.
	UPROPERTY(EditAnywhere, Category = "Condition")
	EUnitState TargetState;
};