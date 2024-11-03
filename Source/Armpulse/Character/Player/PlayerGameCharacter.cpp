// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameCharacter.h"

#include "GameFramework/SpringArmComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "../Components/CharacterStatusComponent.h"

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

    // setup mesh
    CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(RootComponent);
}

void APlayerGameCharacter::BeginPlay()
{
    Super::BeginPlay();

    UCharacterStatusComponent* ParentStatusComponent = GetStatusComponent();
    if (ParentStatusComponent)
    {
        ParentStatusComponent->SetAttackRadius(50.0f);
        ParentStatusComponent->SetMoveSpeed(200.0f);
        ParentStatusComponent->SetCanMove(true);
    }
}