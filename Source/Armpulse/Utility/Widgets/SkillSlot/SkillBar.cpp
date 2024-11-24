#include "SkillBar.h"
#include "SkillSlot.h"

#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

#include "../../../Character/Components/CharacterSkillComponent.h"
#include "../../../Character/Skill/CharacterSkillBase.h"

void USkillBar::InitializeSkillBar(const TArray<TSubclassOf<UCharacterSkillBase>>& ActiveSkills)
{
    if (!SkillBarContainer) return;
    for (int32 Index = 0; Index < ActiveSkills.Num(); Index++)
    {
        const auto& Skill = ActiveSkills[Index];
        USkillSlot* SkillSlot = CreateWidget<USkillSlot>(GetWorld(), SkillSlotClass);
        if (SkillSlot)
        {
            SkillSlot->SetSkillKey(SkillKeys[Index]);
            if (Skill)
            {
                UCharacterSkillBase* SkillInstance = NewObject<UCharacterSkillBase>(this, Skill);
                SkillSlot->SetAssignedSkill(SkillInstance);
            }

            // Add to skill bar UI
            SkillBarContainer->AddChild(SkillSlot);
            UHorizontalBoxSlot* HorizontalSlot = Cast<UHorizontalBoxSlot>(SkillSlot->Slot);
            if (HorizontalSlot)
            {
                HorizontalSlot->SetPadding(FMargin(5.0f, 0.0f, 5.0f, 0.0f));
            }
        }
    }
}

void USkillBar::StartCooldownTimer(int32 SkillIndex)
{
    if (SkillBarContainer && SkillBarContainer->GetChildrenCount() > SkillIndex)
    {
        // Get the child widget at the specified index
        UWidget* SkillSlotWidget = SkillBarContainer->GetChildAt(SkillIndex);

        USkillSlot* SkillSlot = Cast<USkillSlot>(SkillSlotWidget);
        if (SkillSlot)
        {
            SkillSlot->SetSkillCooldown();
        }
    }
}