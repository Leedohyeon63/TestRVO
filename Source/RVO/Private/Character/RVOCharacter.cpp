// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RVOCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "subsystem/UnitSubsystem.h"
#include "AIController.h"

ARVOCharacter::ARVOCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
    //AvoidanceRadius = 90.0f;
    //AvoidanceWeight = 0.5f;
    //UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
    //if (MovementComponent)
    //{
    //    // RVO 충돌 회피 알고리즘 활성화 여부
    //    MovementComponent->bUseRVOAvoidance = true;
    //    // AI가 다른 오브젝트를 감지하고 회피를 시작하는 반경
    //    MovementComponent->AvoidanceConsiderationRadius = AvoidanceRadius;
    //    // 캐릭터 회피 우선 순위(0.0f - 1.0f, 1에 가까울 수록 가중치 높음)
    //    MovementComponent->AvoidanceWeight = AvoidanceWeight;
    //}
    UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
    if (MovementComponent)
    {
        MovementComponent->bUseRVOAvoidance = false;
    }
}

void ARVOCharacter::SetMoveSpeed()
{
}

// Called when the game starts or when spawned
void ARVOCharacter::BeginPlay()
{
	Super::BeginPlay();
    AIController = Cast<AAIController>(GetController());
    if (UUnitSubsystem* Subsystem = GetWorld()->GetSubsystem<UUnitSubsystem>())
    {
        Subsystem->RegisterUnit(this, SideTag);
    }
}

void ARVOCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UUnitSubsystem* Subsystem = GetWorld()->GetSubsystem<UUnitSubsystem>())
    {
        Subsystem->UnregisterUnit(this, SideTag);
    }

    Super::EndPlay(EndPlayReason);
}

void ARVOCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ARVOCharacter::FocusTarget(AActor* InTargetActor, float DeltaTime, float TurnSpeed)
{
    if (!InTargetActor || !IsValid(InTargetActor))
    {
        return false;
    }

    FVector Start = GetActorLocation();
    FVector End = InTargetActor->GetActorLocation(); // InTargetActor 사용

    FRotator TargetRot = UKismetMathLibrary::FindLookAtRotation(Start, End);
    FRotator CurrentRot = GetActorRotation();

    FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, TurnSpeed);

    SetActorRotation(FRotator(CurrentRot.Pitch, NewRot.Yaw, CurrentRot.Roll));

    float DeltaYaw = FMath::Abs(FMath::FindDeltaAngleDegrees(CurrentRot.Yaw, TargetRot.Yaw));
    return DeltaYaw < 5.0f;
}

//void ARVOCharacter::SetRVOAvoidanceEnabled(bool bEnabled)
//{
//    UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
//    if (MovementComponent)
//    {
//        MovementComponent->bUseRVOAvoidance = bEnabled;
//    }
//}

void ARVOCharacter::SetAttackTarget(AActor* InTargetActor)
{
    TargetActor = InTargetActor;
    if (!AIController)
    {
        AIController = Cast<AAIController>(GetController());
    }

    if (AIController)
    {
        UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();
        if (BBComp)
        {
            BBComp->SetValueAsObject(TEXT("AttackTarget"), InTargetActor);
        }
    }
}

void ARVOCharacter::TestAttack()
{
    //if (TargetActor)
    //{
    //    FVector MyLoc = GetActorLocation();
    //    FVector TargetLoc = TargetActor->GetActorLocation();

    //    MyLoc.Z = 0.0f;
    //    TargetLoc.Z = 0.0f;

    //    FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(MyLoc, TargetLoc);

    //    SetActorRotation(LookAtRot);

    //    if (GetController())
    //    {
    //        GetController()->SetControlRotation(LookAtRot);
    //    }
    //}

    if (AttackMontage)
    {
        PlayAnimMontage(AttackMontage);
    }
}

