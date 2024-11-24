#include "SkillSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void USkillSlot::SetSkillCooldown(float NewCooldownDuration)
{
    SkillTotalCooldown = NewCooldownDuration;
    SkillCurrentCooldown = NewCooldownDuration;

    // Show the Cooldown Overlay
    if (SkillCooldownOverlay)
    {
        SkillCooldownOverlay->SetVisibility(ESlateVisibility::Visible);
    }
}

void USkillSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (SkillCurrentCooldown > 0.0f)
    {
        SkillCurrentCooldown -= InDeltaTime;

        // Update Cooldown Overlay Alpha or Scale
        if (SkillCooldownOverlay)
        {
            float Alpha = SkillCurrentCooldown / SkillTotalCooldown;
            SkillCooldownOverlay->SetRenderOpacity(Alpha); // Adjust opacity based on remaining time
        }

        // Update Cooldown Text
        if (SkillCooldownText)
        {
            SkillCooldownText->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), SkillCurrentCooldown)));
        }

        // If cooldown ends, hide the overlay
        if (SkillCurrentCooldown <= 0.0f)
        {
            if (SkillCooldownOverlay)
            {
                SkillCooldownOverlay->SetVisibility(ESlateVisibility::Hidden);
            }
            if (SkillCooldownText)
            {
                SkillCooldownText->SetText(FText::GetEmpty());
            }
        }
    }
}