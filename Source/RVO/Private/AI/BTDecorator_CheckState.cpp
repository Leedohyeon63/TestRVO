#include "AI/BTDecorator_CheckState.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckState::UBTDecorator_CheckState()
{
	NodeName = TEXT("Check Unit State");

	// 기본적으로 'State'라는 이름의 블랙보드 키를 찾도록 설정합니다.
	BlackboardKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CheckState, TargetState), StaticEnum<EUnitState>());
}

bool UBTDecorator_CheckState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return false;

	uint8 CurrentState = BB->GetValueAsEnum(GetSelectedBlackboardKey());

	return CurrentState == static_cast<uint8>(TargetState);
}