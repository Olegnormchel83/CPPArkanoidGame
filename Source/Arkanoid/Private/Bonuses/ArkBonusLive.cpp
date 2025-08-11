// Olegnormchel. All rights reserved


#include "Bonuses/ArkBonusLive.h"

#include "ArkPaddle.h"

AArkBonusLive::AArkBonusLive()
{
	Value = 1.f;
}

void AArkBonusLive::BonusAction(AArkPaddle* Paddle)
{
	Paddle->BonusChangeLives(Value);
	
	Super::BonusAction(Paddle);
}
