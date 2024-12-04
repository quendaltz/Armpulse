// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "../../Components/CharacterCombatComponent.h"
#include "../../Components/CharacterStatusComponent.h"

#include "DrawDebugHelpers.h"

APlayerGameCharacter::APlayerGameCharacter()
{
    // root component is CapsuleComponent from super class >> GameCharacter

    // setup camera
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void APlayerGameCharacter::BeginPlay()
{
    Super::BeginPlay();

    UCharacterStatusComponent* ParentStatusComponent = GetStatusComponent();
    if (ParentStatusComponent)
    {
        ParentStatusComponent->SetAttackPower(35.0f);
        ParentStatusComponent->SetAttackRadius(50.0f);
        ParentStatusComponent->SetAttackSpeed(80.0f);
        ParentStatusComponent->SetMoveSpeed(400.0f);
        ParentStatusComponent->SetIsActing(false);
        ParentStatusComponent->SetCanAct(true);
        ParentStatusComponent->SetCanMove(true);

        float InitialHealth = 200.0f;
        ParentStatusComponent->SetMaxHealth(InitialHealth);
        ParentStatusComponent->SetCurrentHealth(InitialHealth);
        ParentStatusComponent->SetDefense(10.0f);
        UpdateHealthBar(InitialHealth/InitialHealth);
    }
}

void APlayerGameCharacter::AttackTriggered()
{
    UCharacterCombatComponent* ParentCombatComponent = GetCombatComponent();
    UCharacterStatusComponent* ParentStatusComponent = GetStatusComponent();
    if (ParentCombatComponent)
	{
		float ActorCapsuleRadius = 0.0f;
        ActorCapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
        float TargetHitboxRadius = 0.0f;
        TargetHitboxRadius = ParentStatusComponent->GetAttackRadius();

        if (TargetHitboxRadius < 0.0f)
        {
            return;
        }

        FVector HitboxSize = FVector(TargetHitboxRadius, TargetHitboxRadius, 0.0f);
        FCollisionShape AttackHitbox = FCollisionShape::MakeBox(HitboxSize);
        FRotator AttackRotation = GetActorRotation();

		FVector HitboxSpawnLocation = GetForwardCharacterLocation(ActorCapsuleRadius + TargetHitboxRadius);
        DrawDebugBox(GetWorld(), HitboxSpawnLocation, HitboxSize, AttackRotation.Quaternion(), FColor::Green, false, 1.0f); // Duration is 1 second
		ParentCombatComponent->Attack(ParentStatusComponent, AttackHitbox, AttackRotation, HitboxSpawnLocation);
	}
}