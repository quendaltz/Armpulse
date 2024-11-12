#pragma once

#include "CoreMinimal.h"

#include "../Skill/CharacterSkillBase.h"

#include "CharacterSkillComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ARMPULSE_API UCharacterSkillComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCharacterSkillComponent();

    void InitializeSkills(FName CharacterClass, FName WeaponType);
    void ActivateSkill(FName SkillKey);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Skills")
    USkillSet* SkillSet;

    UPROPERTY()
    TMap<FName, USkillBase*> ActiveSkills;
};