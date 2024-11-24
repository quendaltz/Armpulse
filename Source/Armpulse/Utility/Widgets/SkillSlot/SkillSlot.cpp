#include "SkillSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Styling/SlateBrush.h"

#include "../../../Character/Skill/CharacterSkillBase.h"

void USkillSlot::SetAssignedSkill(UCharacterSkillBase* NewSkill)
{
    AssignedSkill = NewSkill;
    UTexture2D* SkillIconTexture = NewSkill->GetSkillIcon();
    if (SkillIcon && SkillIconTexture)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(SkillIconTexture);
        Brush.ImageSize = FVector2D(SkillIconTexture->GetSizeX(), SkillIconTexture->GetSizeY());
        SkillIcon->SetBrush(Brush);
    }
}

void USkillSlot::SetSkillCooldown()
{
    float NewCooldownDuration = AssignedSkill->GetCooldownTime();
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