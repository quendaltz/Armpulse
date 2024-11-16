#include "CharacterSkillComponent.h"

#include "../Character/GameCharacter.h"
#include "../Skill/CharacterSkillBase.h"
#include "../Skill/SkillSet/SkillSet.h"
#include "../Skill/Skills/SwordRushSkill.h"


UCharacterSkillComponent::UCharacterSkillComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterSkillComponent::InitializeSkills()
{
    // Load skills based on character class and weapon type
    // ActiveSkills.Empty();

    // USwordRushSkill* SwordRushSkill = NewObject<USwordRushSkill>(this);

    // ActiveSkills.Add("Sword Rush", SwordRushSkill);
    // if (SkillSet)
    // {
    //     for (const auto& Elem : SkillSet->ClassSkills)
    //     {
    //         if (Elem.Key == CharacterClass)
    //         {
    //             UCharacterSkillBase* NewSkill = NewObject<UCharacterSkillBase>(this, Elem.Value);
    //             ActiveSkills.Add(Elem.Key, NewSkill);
    //         }
    //     }

    //     for (const auto& Elem : SkillSet->WeaponSkills)
    //     {
    //         if (Elem.Key == WeaponType)
    //         {
    //             UCharacterSkillBase* NewSkill = NewObject<UCharacterSkillBase>(this, Elem.Value);
    //             ActiveSkills.Add(Elem.Key, NewSkill);
    //         }
    //     }
    // }
}

void UCharacterSkillComponent::ActivateSkill(FName SkillName)
{
    
    AGameCharacter* OwnerCharacter = Cast<AGameCharacter>(GetOwner());
    AController* OwnerInstigator = GetOwner()->GetInstigatorController();

    if (OwnerCharacter && ActiveSkills.Contains(SkillName))
    {
        TSubclassOf<UCharacterSkillBase> Skill = *ActiveSkills.Find(SkillName);
        if (Skill)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sword Rush Found!"));
            UCharacterSkillBase* SkillInstance = NewObject<UCharacterSkillBase>(this, Skill);
            SkillInstance->ActivateSkill(OwnerCharacter, OwnerInstigator);
        }
    }
}