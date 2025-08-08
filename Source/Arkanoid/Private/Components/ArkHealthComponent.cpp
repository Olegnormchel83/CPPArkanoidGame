// Olegnormchel. All rights reserved


#include "Components/ArkHealthComponent.h"

UArkHealthComponent::UArkHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UArkHealthComponent::SetHealth(const int32 NewHealth)
{
	Health = FMath::Abs(NewHealth);
}

void UArkHealthComponent::TakeDamage(const int32 Damage)
{
	Health = FMath::Max(Health - Damage, 0);
}

