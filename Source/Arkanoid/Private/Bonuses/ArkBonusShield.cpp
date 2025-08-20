// Olegnormchel. All rights reserved

#include "ArkBonusShield.h"

#include "ArkPaddle.h"

AArkBonusShield::AArkBonusShield()
{
	Duration = 8.f;
}

void AArkBonusShield::BonusAction(AArkPaddle* Paddle)
{
	if (!Paddle) return;

	Paddle->BonusSpawnShield(Duration);
	
	Super::BonusAction(Paddle);
}

