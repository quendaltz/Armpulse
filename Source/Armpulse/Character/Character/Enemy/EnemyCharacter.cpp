// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "../../Components/CharacterStatusComponent.h"

AEnemyCharacter::AEnemyCharacter()
{

}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    UCharacterStatusComponent* ParentStatusComponent = GetStatusComponent();
    if (ParentStatusComponent)
    {
        float InitialHealth = 100.0f;
        ParentStatusComponent->SetMaxHealth(InitialHealth);
        ParentStatusComponent->SetCurrentHealth(InitialHealth);
        ParentStatusComponent->SetDefense(5.0f);
        UpdateHealthBar(InitialHealth/InitialHealth);
    }
}