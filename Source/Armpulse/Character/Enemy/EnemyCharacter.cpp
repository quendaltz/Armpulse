// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Components/SkeletalMeshComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
    CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(RootComponent);
}