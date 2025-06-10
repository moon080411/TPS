// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/TPSAnimInstance.h"
#include "Character/TPSCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UTPSAnimInstance::UTPSAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> FireMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Fire.AM_Fire'"));
	if (FireMontageRef.Succeeded())
	{
		FireMontage = FireMontageRef.Object;
	}
}

void UTPSAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ATPSCharacter>(TryGetPawnOwner());

	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UTPSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

		if (Character == nullptr)
			return;
		else if (MovementComponent == nullptr)
			return;
		Velocity = MovementComponent->Velocity;

		FVector FworwardVector = Character->GetActorForwardVector();
		ForwardSpeed = FVector::DotProduct(Velocity, FworwardVector);

		FVector RightVector = Character->GetActorRightVector();
		RightSpeed = FVector::DotProduct(Velocity, RightVector);

		bSouldMove = (Velocity.Size2D() > 3.0f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);
		
		bIsFalling = MovementComponent->IsFalling();

}

void UTPSAnimInstance::PlayFireMontage()
{
	Montage_Play(FireMontage);
}
