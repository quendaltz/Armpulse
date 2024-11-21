#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameCharacter.generated.h"

class UCapsuleComponent;
class UAnimMontage;
class UWidgetComponent;
UCLASS()
class ARMPULSE_API AGameCharacter : public APawn
{
	GENERATED_BODY()

public:
	AGameCharacter();

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	// class UPaperFlipbookComponent* CharacterFlipbook;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// class UPaperFlipbook* IdleFlipbook;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// class UPaperFlipbook* RunFlipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* CharacterMesh;

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	// character box
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;
	// components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UCharacterStatusComponent* StatusComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UCharacterCombatComponent* CombatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UCharacterSkillComponent* SkillComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UCharacterDashComponent* DashComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    UAnimSequence* MoveAnimation;
	UAnimSequence* CurrentAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UDamageWidget> DamageWidgetClass;

	// widgets
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* DamageWidgetComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBarComponent;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }
	FORCEINLINE UCharacterStatusComponent* GetStatusComponent() const { return StatusComponent; }
	FORCEINLINE UCharacterCombatComponent* GetCombatComponent() const { return CombatComponent; }
	FORCEINLINE UCharacterDashComponent* GetDashComponent() const { return DashComponent; }

	FVector GetForwardCharacterLocation(float ForwardDistance = 0.0f);

    void ExecuteMontage(UAnimMontage* TargetMontage, bool DynamicDuration = false, float DesiredDuration = 0.0f);
	void PauseMontage(UAnimMontage* TargetMontage, float PauseTime, float PauseDuration, float ResumePlayRate = 1.0f);
	void ResumeMontage(UAnimMontage* TargetMontage);
	void SetMontagePlayRate(UAnimMontage* TargetMontage, float PlayRate);
    void ExecuteAnimation(UAnimSequence* AnimationToPlay, bool bLoop = false);

	void MoveTriggered(const struct FInputActionValue& Value);
	void MoveCompleted(const struct FInputActionValue& Value);
	void AttackTriggered();
	void CastSkill(FName SkillName);
	void DisplayDamage(float Damage, AGameCharacter* HitActor);
	void UpdateHealthBar(float HealthPercent);
};
