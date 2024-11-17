#include "CharacterSkillComponent.h"

#include "CharacterStatusComponent.h"
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

void UCharacterSkillComponent::CastSkill(FName SkillName, UCharacterStatusComponent* CharacterStatusComponent)
{
    AGameCharacter* OwnerCharacter = Cast<AGameCharacter>(GetOwner());
    AController* OwnerInstigator = GetOwner()->GetInstigatorController();

    if (OwnerCharacter && CharacterStatusComponent && ActiveSkills.Contains(SkillName))
    {
        bool IsActing = CharacterStatusComponent->GetIsActing();
        bool CanAction = CharacterStatusComponent->GetCanAct();
        if (!CanAction && IsActing) return;

        TSubclassOf<UCharacterSkillBase> Skill = *ActiveSkills.Find(SkillName);
        if (Skill)
        {
            FTimerDelegate TimerFunction;
            TimerFunction.BindLambda([this, CharacterStatusComponent]()
            {
                CharacterStatusComponent->ResetActionState();
            });

            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sword Rush Found!"));
            UCharacterSkillBase* SkillInstance = NewObject<UCharacterSkillBase>(this, Skill);
            float ActionLockTime = SkillInstance->GetActionLockTime();
            float SkillCooldownTime = SkillInstance->GetCooldownTime();

            CharacterStatusComponent->SetIsActing(true);
	        CharacterStatusComponent->SetCanAct(false);
            SkillInstance->ActivateSkill(OwnerCharacter, OwnerInstigator);

            GetWorld()->GetTimerManager().SetTimer(ActionTimer, TimerFunction, ActionLockTime, false);
        }
    }
}