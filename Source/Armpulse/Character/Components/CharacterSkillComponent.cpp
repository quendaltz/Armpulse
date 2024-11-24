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

void UCharacterSkillComponent::InitializeSkills()
{
    // set in blueprint
    

    // Load skills based on character class and weapon type
    // ActiveSkills.Empty();

    //USwordRushSkill* SwordRushSkill = NewObject<USwordRushSkill>(this);
    //ActiveSkills[0] = USwordRushSkill::StaticClass();

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
            //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Skill [0] Found!"));

            UCharacterSkillBase* SkillInstance = NewObject<UCharacterSkillBase>(this, Skill);
            UE_LOG(LogTemp, Display, TEXT("%d"), IsCooldown);
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