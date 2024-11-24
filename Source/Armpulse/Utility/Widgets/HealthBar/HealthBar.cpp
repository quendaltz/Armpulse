#include "HealthBar.h"
#include "Components/ProgressBar.h"

void UHealthBar::UpdateHealthProgressBar(float TargetHealthPercent)
{
    if (HealthProgressBar)
    {
        TargetHealthPercent = FMath::Clamp(TargetHealthPercent, 0.0f, 1.0f);
        HealthProgressBar->SetPercent(TargetHealthPercent);

        if (TargetHealthPercent <= 0.0f)
        {
            HealthProgressBar->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}