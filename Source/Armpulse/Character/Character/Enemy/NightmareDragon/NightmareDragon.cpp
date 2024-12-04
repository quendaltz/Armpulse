#include "NightmareDragon.h"

#include "../../../Components/CharacterCombatComponent.h"
#include "../../../Components/CharacterStatusComponent.h"

ANightmareDragon::ANightmareDragon()
{

}

void ANightmareDragon::BeginPlay()
{
    Super::BeginPlay();

    UCharacterStatusComponent* ParentStatusComponent = GetStatusComponent();
    if (ParentStatusComponent)
    {
        ParentStatusComponent->SetAttackPower(50.0f);
        ParentStatusComponent->SetAttackRadius(200.0f);
        // attack animation time = 100.0f/AttackSpeed
        ParentStatusComponent->SetAttackSpeed(25.0f);

        ParentStatusComponent->SetIsActing(false);
        ParentStatusComponent->SetCanAct(true);
        ParentStatusComponent->SetCanMove(true);

        float InitialHealth = 1000.0f;
        ParentStatusComponent->SetMaxHealth(InitialHealth);
        ParentStatusComponent->SetCurrentHealth(InitialHealth);
        ParentStatusComponent->SetDefense(10.0f);
        UpdateHealthBar(InitialHealth/InitialHealth);
    }

    GetWorld()->GetTimerManager().SetTimer(
        AttackTimerHandle,
        this,
        &ANightmareDragon::SweepAttack,
        10.0f,
        true
    );
}

void ANightmareDragon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ANightmareDragon::PerformAction()
{
    float GameTime = GetWorld()->GetTimeSeconds();

    // if (GameTime%90.0f == 0)
    // {
    //     // ultimate
    // }
}

void ANightmareDragon::SweepAttack()
{
    UCharacterStatusComponent* ParentStatusComponent = GetStatusComponent();
    UCharacterCombatComponent* ParentCombatComponent = GetCombatComponent();
    if (ParentCombatComponent)
	{
        float PrepareTime = 3.0f; // show attack area before play animation
        float ProcessAttackAfterAnimationTime = 2.0f; // after play animation
        // calculate attack after PrepareTime + ProcessAttackAfterAnimationTime
        FVector AttackCenterLocation = GetForwardCharacterLocation(200.0f);
        AttackCenterLocation.Z = 0.0f;
        float HitboxSize = ParentStatusComponent->GetAttackRadius();
        FCollisionShape AttackHitbox = FCollisionShape::MakeSphere(HitboxSize);
        FRotator AttackRotation = GetActorRotation();

        FTimerHandle SweepAttackTimerHandle;
        FTimerDelegate AttackFunction;
        AttackFunction.BindLambda([ParentStatusComponent, ParentCombatComponent, AttackHitbox, AttackCenterLocation, ProcessAttackAfterAnimationTime]()
        {
            ParentCombatComponent->Attack(ParentStatusComponent, AttackHitbox, FRotator::ZeroRotator, AttackCenterLocation, ProcessAttackAfterAnimationTime);
        });

        SpawnCircleDecal(AttackCenterLocation, HitboxSize, PrepareTime + ProcessAttackAfterAnimationTime);
        DrawDebugSphere(GetWorld(), AttackCenterLocation, HitboxSize, 8, FColor::Green, false, 1.0f); // Duration is 1 second
        GetWorld()->GetTimerManager().SetTimer(SweepAttackTimerHandle, AttackFunction, PrepareTime, false);
	}
}