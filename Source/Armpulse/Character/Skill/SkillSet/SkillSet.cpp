#include "SkillSet.h"

TSubclassOf<UCharacterSkillBase> USkillSet::GetSkill(FName SkillKey) const
{
    // Priority logic: Check weapon skills first, then class skills
    if (WeaponSkills.Contains(SkillKey))
    {
        return WeaponSkills[SkillKey];
    }
    else if (ClassSkills.Contains(SkillKey))
    {
        return ClassSkills[SkillKey];
    }
    return nullptr;
}