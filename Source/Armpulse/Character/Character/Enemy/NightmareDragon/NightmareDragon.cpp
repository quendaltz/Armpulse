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
        ParentStatusComponent->SetAttackRadius(100.0f);
        ParentStatusComponent->SetAttackSpeed(20.0f);

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
        //ShowAttackArea(GetActorLocation() + FVector(0, 0, 10), GetActorRotation(), 5.0f);
        //ParentCombatComponent->PrepareAttack(5.0f);
		//ParentCombatComponent->Attack(ParentStatusComponent);
        UE_LOG(LogTemp, Display, TEXT("drag atrtackl"));
	}
}