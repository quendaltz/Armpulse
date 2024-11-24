#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlot.generated.h"

class UCharacterSkillBase;
class UImage;
class UTextBlock;
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
    UImage* SkillIcon;

    UPROPERTY(meta = (BindWidget)) // Bound to the Cooldown Overlay widget
    UImage* SkillCooldownOverlay;

    UPROPERTY(meta = (BindWidget)) // Bound to the Cooldown Text widget
    UTextBlock* SkillCooldownText;

    UPROPERTY(meta = (BindWidget)) // Bound to the Cooldown Text widget
    UTextBlock* SkillKeyText;

    UFUNCTION(BlueprintCallable)
    void SetAssignedSkill(UCharacterSkillBase* NewSkill);
    void SetSkillKey(FString Key);
    
    void SetSkillCooldown();

protected:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
    float SkillCurrentCooldown;
    float SkillTotalCooldown;
    
    UCharacterSkillBase* AssignedSkill;
};
