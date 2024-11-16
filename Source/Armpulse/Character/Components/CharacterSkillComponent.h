#pragma once

#include "CoreMinimal.h"

#include "../Skill/CharacterSkillBase.h"

#include "CharacterSkillComponent.generated.h"

class UCharacterStatusComponent;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ARMPULSE_API UCharacterSkillComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCharacterSkillComponent();

    void InitializeSkills();
    //void InitializeSkills(FName CharacterClass, FName WeaponType);
    void CastSkill(FName SkillName, UCharacterStatusComponent* CharacterStatusComponent);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Skills")
    class USkillSet* SkillSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    TMap<FName, TSubclassOf<UCharacterSkillBase>> ActiveSkills;

private:
	FTimerHandle ActionTimer;
};