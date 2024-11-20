#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

UCLASS()
class ARMPULSE_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    void UpdateHealthProgressBar(float TargetHealthPercent);

protected:
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthProgressBar;
};
