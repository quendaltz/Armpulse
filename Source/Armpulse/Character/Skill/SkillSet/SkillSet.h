#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../CharacterSkillBase.h"

#include "SkillSet.generated.h"

UCLASS(Blueprintable)
class ARMPULSE_API USkillSet : public UObject
{
    GENERATED_BODY()

public:
    TSubclassOf<UCharacterSkillBase> GetSkill(FName SkillKey) const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skills")
    TMap<FName, TSubclassOf<UCharacterSkillBase>> ClassSkills; // Skills based on character class

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skills")
    TMap<FName, TSubclassOf<UCharacterSkillBase>> WeaponSkills; // Skills based on weapon type
};