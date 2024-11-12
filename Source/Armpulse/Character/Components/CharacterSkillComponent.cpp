#include "CharacterSkillComponent.h"

#include "../Skill/CharacterSkillBase.h"

UCharacterSkillComponent::UCharacterSkillComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterSkillComponent::InitializeSkills(FName CharacterClass, FName WeaponType)
{
    // Load skills based on character class and weapon type
    ActiveSkills.Empty();

    if (SkillSet)
    {
        for (const auto& Elem : SkillSet->ClassSkills)
        {
            if (Elem.Key == CharacterClass)
            {
                USkillBase* NewSkill = NewObject<USkillBase>(this, Elem.Value);
                ActiveSkills.Add(Elem.Key, NewSkill);
            }
        }

        for (const auto& Elem : SkillSet->WeaponSkills)
        {
            if (Elem.Key == WeaponType)
            {
                USkillBase* NewSkill = NewObject<USkillBase>(this, Elem.Value);
                ActiveSkills.Add(Elem.Key, NewSkill);
            }
        }
    }
}

void UCharacterSkillComponent::ActivateSkill(FName SkillKey)
{
    if (ActiveSkills.Contains(SkillKey))
    {
        ActiveSkills[SkillKey]->ActivateSkill(GetOwner());
    }
}