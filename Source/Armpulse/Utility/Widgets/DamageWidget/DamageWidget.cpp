#include "DamageWidget.h"
#include "Components/TextBlock.h"

void UDamageWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (DamageText)
    {
        DamageText->SetShadowOffset(FVector2D(0.0f, 0.0f));
        DamageText->SetShadowColorAndOpacity(FLinearColor::Transparent);
    }
}

void UDamageWidget::SetDamageValue(float Damage)
{
    if (DamageText)
    {
        DamageText->SetText(FText::AsNumber(FMath::RoundToInt(Damage)));
    }
}

void UDamageWidget::PlayDamageAnimation()
{
    if (DamageAnimation)
    {
        PlayAnimation(DamageAnimation);
    }
}