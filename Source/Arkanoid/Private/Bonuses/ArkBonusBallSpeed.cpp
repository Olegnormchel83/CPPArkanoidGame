// Olegnormchel. All rights reserved


#include "Bonuses/ArkBonusBallSpeed.h"

#include "ArkPaddle.h"

AArkBonusBallSpeed::AArkBonusBallSpeed()
{
	Value = -0.5f;
}

void AArkBonusBallSpeed::BonusAction(AArkPaddle* Paddle)
{
	Paddle->BonusChangeBallSpeed(Value);
	
	Super::BonusAction(Paddle);
}
