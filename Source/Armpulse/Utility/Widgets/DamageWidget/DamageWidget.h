#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageWidget.generated.h"

UCLASS()
class ARMPULSE_API UDamageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetDamageValue(float Damage);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void PlayDamageAnimation();

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* DamageText;

    UPROPERTY(meta = (BindWidgetAnim), Transient, BlueprintReadWrite, Category = "Animation")
    UWidgetAnimation* DamageAnimation;
};
