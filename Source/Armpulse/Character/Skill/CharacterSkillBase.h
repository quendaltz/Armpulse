#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterSkillBase.generated.h"

class AGameCharacter;
UCLASS(Blueprintable, BlueprintType)
class ARMPULSE_API UCharacterSkillBase : public UObject
{
    GENERATED_BODY()

public:
    virtual void ActivateSkill(AGameCharacter* Instigator, AController* InstigatorController); // Base function to activate the skill

    FORCEINLINE float GetActionLockTime() const { return ActionLockTime; }
    FORCEINLINE float GetCooldownTime() const { return CooldownTime; }
    FORCEINLINE UTexture2D* GetSkillIcon() const { return SkillIcon; }
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
    FName SkillName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
    float ActionLockTime;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
    float CooldownTime;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
    UTexture2D* SkillIcon;
};