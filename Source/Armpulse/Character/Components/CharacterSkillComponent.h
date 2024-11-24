#pragma once

#include "CoreMinimal.h"

#include "CharacterSkillComponent.generated.h"

class UCharacterStatusComponent;
class UCharacterSkillBase;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ARMPULSE_API UCharacterSkillComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCharacterSkillComponent();

    void InitializeSkills();
    //void InitializeSkills(FName CharacterClass, FName WeaponType);
    bool CastSkill(int32 SkillIndex, UCharacterStatusComponent* CharacterStatusComponent);

    FORCEINLINE TArray<TSubclassOf<UCharacterSkillBase>> GetActiveSkills() const { return ActiveSkills; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Skills")
    class USkillSet* SkillSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    TArray<TSubclassOf<UCharacterSkillBase>> ActiveSkills;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    TArray<bool> CooldownSkills;
};