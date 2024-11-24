#include "SkillBar.h"
#include "SkillSlot.h"

// void USkillBarWidget::InitializeSkillBar(const TMap<FName, USkillBase*>& ActiveSkills)
// {
//     for (const auto& SkillPair : ActiveSkills)
//     {
//         USkillSlotWidget* SkillSlot = CreateWidget<USkillSlotWidget>(GetWorld(), SkillSlotClass);
//         if (SkillSlot)
//         {
//             // Set initial icon, cooldown, etc.
//             SkillSlot->SetCooldown(SkillPair.Value->GetCooldownTime());

//             // Add to skill bar UI
//             SkillBarContainer->AddChild(SkillSlot);
//         }
//     }
// }