// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Components/SkeletalMeshComponent.h"

#include "../../Components/CharacterStatusComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
    CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(RootComponent);
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    UCharacterStatusComponent* ParentStatusComponent = GetStatusComponent();
    if (ParentStatusComponent)
    {
        ParentStatusComponent->SetHealth(100.0f);
        ParentStatusComponent->SetDefense(5.0f);
    }
}