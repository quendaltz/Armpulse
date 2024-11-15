#pragma once

#include "CoreMinimal.h"
#include "../CharacterSkillBase.h"
#include "SwordRushSkill.generated.h"

UCLASS()
class ARMPULSE_API USwordRushSkill : public UCharacterSkillBase
{
    GENERATED_BODY()

public:
    virtual void ActivateSkill(AGameCharacter* Instigator) override;
};