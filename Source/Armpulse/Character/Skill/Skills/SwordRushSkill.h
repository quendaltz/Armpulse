#pragma once

#include "CoreMinimal.h"
#include "../CharacterSkillBase.h"
#include "SwordRushSkill.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ARMPULSE_API USwordRushSkill : public UCharacterSkillBase
{
    GENERATED_BODY()

public:
    USwordRushSkill();
    virtual void ActivateSkill(AGameCharacter* Instigator, AController* InstigatorController) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* SwordRushMontage;
};