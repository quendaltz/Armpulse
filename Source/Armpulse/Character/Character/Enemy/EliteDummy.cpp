// Fill out your copyright notice in the Description page of Project Settings.


#include "EliteDummy.h"

#include "../../Components/CharacterStatusComponent.h"

AEliteDummy::AEliteDummy()
{

}

void AEliteDummy::BeginPlay()
{
    Super::BeginPlay();

    UCharacterStatusComponent* ParentStatusComponent = GetStatusComponent();
    if (ParentStatusComponent)
    {
        float InitialHealth = 200.0f;
        ParentStatusComponent->SetMaxHealth(InitialHealth);
        ParentStatusComponent->SetCurrentHealth(InitialHealth);
        ParentStatusComponent->SetDefense(10.0f);
        UpdateHealthBar(InitialHealth/InitialHealth);
    }
}