#include "CharacterSkillComponent.h"

#include "CharacterStatusComponent.h"
#include "../Character/GameCharacter.h"
#include "../Skill/CharacterSkillBase.h"
#include "../Skill/SkillSet/SkillSet.h"
#include "../Skill/Skills/SwordRushSkill.h"


UCharacterSkillComponent::UCharacterSkillComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    ActiveSkills.Init(nullptr, 4);
    CooldownSkills.Init(false, 4);
}

bool UCharacterSkillComponent::CastSkill(int32 SkillIndex, UCharacterStatusComponent* CharacterStatusComponent)
{
    AGameCharacter* OwnerCharacter = Cast<AGameCharacter>(GetOwner());
    AController* OwnerInstigator = GetOwner()->GetInstigatorController();

    if (OwnerCharacter && CharacterStatusComponent && ActiveSkills.IsValidIndex(SkillIndex) && ActiveSkills[SkillIndex] != nullptr)
    {
        bool IsActing = CharacterStatusComponent->GetIsActing();
        bool CanAction = CharacterStatusComponent->GetCanAct();
        bool IsCooldown = CooldownSkills[SkillIndex];
        if (!CanAction || IsActing || IsCooldown) return false;

        TSubclassOf<UCharacterSkillBase> Skill = *ActiveSkills[SkillIndex];
        if (Skill)
        {
            UCharacterSkillBase* SkillInstance = NewObject<UCharacterSkillBase>(this, Skill);
            if (IsCooldown) return false;

            FTimerHandle ResetActionTimer;
            FTimerDelegate ResetActionFunction;
            ResetActionFunction.BindLambda([this, CharacterStatusComponent]()
            {
                CharacterStatusComponent->ResetActionState();
            });

            FTimerHandle ResetCooldownTimer;
            FTimerDelegate ResetCooldownFunction;
            ResetCooldownFunction.BindLambda([this, SkillIndex]()
            {
                CooldownSkills[SkillIndex] = false;
            });

            float ActionLockTime = SkillInstance->GetActionLockTime();
            float SkillCooldownTime = SkillInstance->GetCooldownTime();

            CooldownSkills[SkillIndex] = true;
            CharacterStatusComponent->SetIsActing(true);
	        CharacterStatusComponent->SetCanAct(false);
            SkillInstance->ActivateSkill(OwnerCharacter, OwnerInstigator);

            GetWorld()->GetTimerManager().SetTimer(ResetActionTimer, ResetActionFunction, ActionLockTime, false);
            GetWorld()->GetTimerManager().SetTimer(ResetCooldownTimer, ResetCooldownFunction, SkillCooldownTime, false);
        }
        return true;
    }

    return false;
}