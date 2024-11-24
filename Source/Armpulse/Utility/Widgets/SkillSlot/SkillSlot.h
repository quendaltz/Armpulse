#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlot.generated.h"

UCLASS()
class ARMPULSE_API USkillSlot : public UUserWidget
{
	GENERATED_BODY()

public:
    //UFUNCTION(BlueprintCallable, Category = "UI")
    

protected:
    //UPROPERTY(meta = (BindWidget))

public:
    UPROPERTY(meta = (BindWidget)) // Bound to the Skill Icon widget
    class UImage* SkillIcon;

    UPROPERTY(meta = (BindWidget)) // Bound to the Cooldown Overlay widget
    class UImage* SkillCooldownOverlay;

    UPROPERTY(meta = (BindWidget)) // Bound to the Cooldown Text widget
    class UTextBlock* SkillCooldownText;

    UFUNCTION(BlueprintCallable)
    void SetSkillCooldown(float NewCooldownDuration);

protected:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
    float SkillCurrentCooldown;
    float SkillTotalCooldown;
    
};
