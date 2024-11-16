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

    void InitializeSkills();
    //void InitializeSkills(FName CharacterClass, FName WeaponType);
    void ActivateSkill(FName SkillName);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Skills")
    class USkillSet* SkillSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    TMap<FName, TSubclassOf<UCharacterSkillBase>> ActiveSkills;
};