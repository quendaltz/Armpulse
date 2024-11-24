// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"

#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "../Components/CharacterCombatComponent.h"
#include "../Components/CharacterSkillComponent.h"
#include "../Components/CharacterStatusComponent.h"
#include "../Components/Movement/CharacterDashComponent.h"
#include "../../Utility/BaseGameConfig.h"
#include "../../Utility/Widgets/DamageWidget/DamageWidget.h"
#include "../../Utility/Widgets/HealthBar/HealthBar.h"

#include "DrawDebugHelpers.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	// CharacterFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("CharacterFlipbook"));
	// CharacterFlipbook->SetupAttachment(RootComponent);

	// Setup gameplay components
	CombatComponent = CreateDefaultSubobject<UCharacterCombatComponent>(TEXT("CombatComponent"));
	SkillComponent = CreateDefaultSubobject<UCharacterSkillComponent>(TEXT("SkillComponent"));
	StatusComponent = CreateDefaultSubobject<UCharacterStatusComponent>(TEXT("StatusComponent"));
	DashComponent = CreateDefaultSubobject<UCharacterDashComponent>(TEXT("DashComponent"));

	// Setup display component
	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(RootComponent);

	DamageWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidgetComponent"));
    DamageWidgetComponent->SetupAttachment(CharacterMesh);
	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComponent"));
    HealthBarComponent->SetupAttachment(CharacterMesh);
}

// Called when thDamageWidgetComponente game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (SkillComponent)
    {
        SkillComponent->InitializeSkills();
    }
	CurrentAnimation = nullptr;
	DamageWidgetComponent->SetCastShadow(false);

	HealthBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CapsuleComponent)
    {
        FVector CapsuleLocation = CapsuleComponent->GetComponentLocation();
        float CapsuleRadius = CapsuleComponent->GetScaledCapsuleRadius();
        float CapsuleHalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
        
        FColor DebugColor = FColor::Red;
        float Duration = 0.0f; // The sphere will stay for 5 seconds
        float Thickness = 2.0f; // Optional, for the line thickness

        DrawDebugCapsule(GetWorld(), CapsuleLocation, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, DebugColor, false, Duration, 0, Thickness);
    }

	if (StatusComponent)
	{
		auto Test = StatusComponent->GetCurrentHealth();
		//UE_LOG(LogTemp, Warning, TEXT("Hit: %s, %f"), *this->GetName(), Test);
	}
}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// override
float AGameCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// override
	if (CombatComponent)
    {
        float DamageTakenAmount = CombatComponent->HandleTakeDamage(StatusComponent, DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		float CurrentHealth = StatusComponent->GetCurrentHealth();
		float CurrentHealthPercent = CurrentHealth / StatusComponent->GetMaxHealth();
		UpdateHealthBar(CurrentHealthPercent);
		DisplayDamage(DamageTakenAmount, this);

		if (CurrentHealth <= 0.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Die: %s, HP: %f"), *this->GetName(), CurrentHealth);
			Die();
		}
    }
    
    return DamageAmount;
}

FVector AGameCharacter::GetForwardCharacterLocation(float ForwardDistance)
{
	FVector CurrentLocation = GetActorLocation();
	FVector RightVector = GetActorRightVector();
	return CurrentLocation + (RightVector * ForwardDistance);
}

void AGameCharacter::ExecuteMontage(UAnimMontage* TargetMontage, bool DynamicDuration, float DesiredDuration)
{
	if (CharacterMesh)
	{
		UAnimInstance* AnimInstance = CharacterMesh->GetAnimInstance();
		if (AnimInstance)
		{
			float PlayRate = 1.0f; // default playrate
			if (DynamicDuration && DesiredDuration > 0.0f)
			{
				float OriginalDuration = TargetMontage->GetPlayLength();
				PlayRate = OriginalDuration / DesiredDuration;
			}

			if (CurrentAnimation)
			{
				CurrentAnimation = nullptr;
				CharacterMesh->SetAnimation(nullptr);
				CharacterMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			}
			
			CharacterMesh->GetAnimInstance()->Montage_Stop(0.0f);
			CharacterMesh->GetAnimInstance()->Montage_Play(TargetMontage, PlayRate);
		}
	}
}

void AGameCharacter::PauseMontage(UAnimMontage* TargetMontage, float PauseTime, float PauseDuration, float ResumePlayRate)
{
	UAnimInstance* AnimInstance = CharacterMesh->GetAnimInstance();
    if (TargetMontage && AnimInstance)
	{
		FTimerHandle PauseMontageTimerHandle;
        FTimerDelegate PauseMontageFunction;
        PauseMontageFunction.BindLambda([AnimInstance, TargetMontage]()
        {
            AnimInstance->Montage_Pause(TargetMontage);
        });
        GetWorld()->GetTimerManager().SetTimer(PauseMontageTimerHandle, PauseMontageFunction, PauseTime, false);

		FTimerHandle ResumeTimerHandle;
		FTimerDelegate ResumeMontageFunction;
		ResumeMontageFunction.BindLambda([AnimInstance, TargetMontage, ResumePlayRate]()
        {
			AnimInstance->Montage_SetPlayRate(TargetMontage, ResumePlayRate);
            AnimInstance->Montage_Resume(TargetMontage);
        });
		GetWorld()->GetTimerManager().SetTimer(ResumeTimerHandle, ResumeMontageFunction, PauseDuration, false);
	}
}

void AGameCharacter::ResumeMontage(UAnimMontage* TargetMontage)
{
	UAnimInstance* AnimInstance = CharacterMesh->GetAnimInstance();
    if (TargetMontage && AnimInstance)
	{
		AnimInstance->Montage_Resume(TargetMontage);
	}   
}

void AGameCharacter::SetMontagePlayRate(UAnimMontage* TargetMontage, float PlayRate)
{
	UAnimInstance* AnimInstance = CharacterMesh->GetAnimInstance();
    if (TargetMontage && AnimInstance)
	{
		AnimInstance->Montage_SetPlayRate(TargetMontage, PlayRate);
	}   
}

void AGameCharacter::ExecuteAnimation(UAnimSequence* AnimationToPlay, bool bLoop)
{
	if (CharacterMesh)
	{
		CharacterMesh->PlayAnimation(AnimationToPlay, true);
	}
}

void AGameCharacter::MoveTriggered(const FInputActionValue& Value)
{
	FVector2D MoveActionValue = Value.Get<FVector2D>();
	if (StatusComponent->GetCanMove() && StatusComponent->GetCanAct())
	{
		bool bIsMoving = !MoveActionValue.IsNearlyZero(); // input value -> moving
		if (MoveAnimation)
		{
			if (bIsMoving && CurrentAnimation != MoveAnimation)
			{
				ExecuteAnimation(MoveAnimation, true);
				CurrentAnimation = MoveAnimation;
			}
			else if (!bIsMoving && CurrentAnimation == MoveAnimation)
			{
				CurrentAnimation = nullptr;
				CharacterMesh->SetAnimation(nullptr); // Loop idle animation
				CharacterMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			}
		}

		if (bIsMoving)
		{
			MoveActionValue.Normalize();
			float DeltaTime = GetWorld()->DeltaTimeSeconds;

			FVector2D MoveDistance = MoveActionValue * StatusComponent->GetMoveSpeed() * DeltaTime;
			FVector CurrentLocation = GetActorLocation();
			// set initial desired location
			FVector NewLocation = CurrentLocation + FVector(MoveDistance.X, -MoveDistance.Y, 0.0f);

			float ActorCapsuleRadius = CapsuleComponent->GetScaledCapsuleRadius();
			FHitResult HitResult;
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(this);  // Ignore self
			bool bHit = GetWorld()->SweepSingleByChannel(
				HitResult,
				CurrentLocation,
				NewLocation,
				FQuat::Identity,
				ECC_Visibility,
				FCollisionShape::MakeSphere(ActorCapsuleRadius),
				CollisionParams
			);

			if (!bHit) // blocked by obstacle
			{
				SetActorLocation(NewLocation); // Stop moving if collision found
			}

			// rotate character
			FVector MoveDirection = (BaseGameConfig::BaseCharacterForwardDirection() * MoveActionValue.Y) + (BaseGameConfig::BaseCharacterRightDirection() * MoveActionValue.X);
			MoveDirection.Normalize();
			FRotator NewRotation = MoveDirection.Rotation();
			SetActorRotation(NewRotation);
		}
	}
}

void AGameCharacter::MoveCompleted(const FInputActionValue& Value)
{
	FVector2D MoveActionValue = Value.Get<FVector2D>();
	if (CurrentAnimation == MoveAnimation && MoveActionValue.IsNearlyZero())
	{
		CurrentAnimation = nullptr;
		CharacterMesh->SetAnimation(nullptr);
		CharacterMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}
}

// void AGameCharacter::MoveTriggered(const FInputActionValue& Value)
// {
// 	FVector2D MoveActionValue = Value.Get<FVector2D>();
// 	if (CanMove)
// 	{
// 		MoveDirection = MoveActionValue;
// 		CharacterFlipbook->SetFlipbook(RunFlipbook);
// 		FVector FlipbookScale = CharacterFlipbook->GetComponentScale();
// 		if (MoveDirection.X < 0.0f)
// 		{
// 			if (FlipbookScale.X < 0.0f)
// 			{
// 				CharacterFlipbook->SetWorldScale3D(FVector(1.0f, FlipbookScale.Y, FlipbookScale.Z));
// 			}
// 		}
// 		else if (MoveDirection.X > 0.0f)
// 		{
// 			if (FlipbookScale.X > 0.0f)
// 			{
// 				CharacterFlipbook->SetWorldScale3D(FVector(-1.0f, FlipbookScale.Y, FlipbookScale.Z));
// 			}
// 		}
// 	}
// }

// void AGameCharacter::MoveCompleted(const FInputActionValue& Value)
// {
// 	MoveDirection = FVector2D(0.0f, 0.0f);
// 	CharacterFlipbook->SetFlipbook(IdleFlipbook);
// }

void AGameCharacter::AttackTriggered()
{
	if (CombatComponent)
	{
		CombatComponent->Attack(StatusComponent);
	}
}

bool AGameCharacter::CastSkill(int32 SkillIndex)
{
	bool CastSuccess = false;
	if (SkillComponent)
	{
		CastSuccess = SkillComponent->CastSkill(SkillIndex, StatusComponent);
	}
	return CastSuccess;
}

void AGameCharacter::DisplayDamage(float Damage, AGameCharacter* HitActor)
{
    if (!HitActor || !DamageWidgetClass) return;

    // Create the widget instance
    //UDamageWidget* DamageWidget = CreateWidget<UDamageWidget>(GetWorld(), DamageWidgetClass);
	UDamageWidget* DamageWidget = Cast<UDamageWidget>(DamageWidgetComponent->GetUserWidgetObject());
    if (DamageWidget && Damage > 0.0f)
    {
        DamageWidget->SetDamageValue(Damage);
		DamageWidget->PlayDamageAnimation();

        // Add to the viewport
        //DamageWidget->AddToViewport();

        // Optionally, position the widget in 3D space
        // FVector HitLocation = HitActor->GetActorLocation();
        // FVector2D ScreenPosition;
        // if (UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), HitLocation, ScreenPosition))
        // {
        //     DamageWidget->SetPositionInViewport(ScreenPosition);
        // }

        // Set a timer to remove the widget after some time
        // GetWorld()->GetTimerManager().SetTimer(RemoveTimer, [DamageWidget]()
        // {
        //     DamageWidget->RemoveFromParent();
        // }, 3.0f, false);
    }
}

void AGameCharacter::UpdateHealthBar(float HealthPercent)
{
	if (!HealthBarComponent) return;

	UHealthBar* HealthBarWidget = Cast<UHealthBar>(HealthBarComponent->GetUserWidgetObject());
	if (HealthBarWidget)
	{
		HealthBarWidget->UpdateHealthProgressBar(HealthPercent);
	}
}

void AGameCharacter::Die()
{
	FTimerHandle DieTimerHandle;
	FTimerDelegate DieFunction;
	DieFunction.BindLambda([this]()
	{
		Destroy();
	});
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, DieFunction, 3.0f, false);
}