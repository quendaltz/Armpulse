#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameCharacter.generated.h"

class AAttackIndicator;
class UAnimMontage;
class UCapsuleComponent;
class UWidgetComponent;
class USkeletalMeshComponent;
class UCharacterStatusComponent;
class UCharacterCombatComponent;
class UCharacterSkillComponent;
class UCharacterDashComponent;
class UDamageWidget;
class UInputComponent;
UCLASS()
class ARMPULSE_API AGameCharacter : public APawn
{
	GENERATED_BODY()

public:
	AGameCharacter();

	FORCEINLINE UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }
	FORCEINLINE AAttackIndicator* GetAttackIndicatorActor() const { return AttackIndicator; }
	FORCEINLINE UCharacterStatusComponent* GetStatusComponent() const { return StatusComponent; }
	FORCEINLINE UCharacterCombatComponent* GetCombatComponent() const { return CombatComponent; }
	FORCEINLINE UCharacterSkillComponent* GetSkillComponent() const { return SkillComponent; }
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
	void SpawnCircleDecal(FVector Location, float AreaRadius, float AreaDuration);
	bool CastSkill(int32 SkillIndex);
	void Die();

	void DisplayDamage(float Damage, AGameCharacter* HitActor);
	void UpdateHealthBar(float HealthPercent);

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	// character box
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CharacterMesh;

	// actor component
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<AAttackIndicator> AttackIndicatorClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AAttackIndicator* AttackIndicator;
	
	// custom components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UCharacterStatusComponent* StatusComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UCharacterCombatComponent* CombatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UCharacterSkillComponent* SkillComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UCharacterDashComponent* DashComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    UAnimSequence* MoveAnimation;
	UAnimSequence* CurrentAnimation;

	// widgets
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UDamageWidget> DamageWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* DamageWidgetComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBarComponent;
};
