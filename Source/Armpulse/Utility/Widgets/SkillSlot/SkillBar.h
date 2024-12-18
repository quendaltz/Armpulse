#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillBar.generated.h"

class USkillSlot;
class UHorizontalBox;
class UCharacterSkillBase;
UCLASS()
class ARMPULSE_API USkillBar : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION()
    void InitializeSkillBar(const TArray<TSubclassOf<UCharacterSkillBase>>& ActiveSkills);
    void StartCooldownTimer(int32 SkillIndex);

protected:
    // Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> SkillSlotClass;

private:
    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* SkillBarContainer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TArray<FString> SkillKeys = { TEXT("A"), TEXT("S"), TEXT("D"), TEXT("F") };
};