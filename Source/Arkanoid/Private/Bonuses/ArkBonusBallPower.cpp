// Olegnormchel. All rights reserved

#include "ArkBonusBallPower.h"

#include "ArkPaddle.h"


// Sets default values
AArkBonusBallPower::AArkBonusBallPower()
{
	Value = 1.f;
	Duration = 10.f;
}

void AArkBonusBallPower::BonusAction(AArkPaddle* Paddle)
{
	if (!Paddle) return;
	Paddle->BonusChangeBallPower(Value, Duration);
	
	Super::BonusAction(Paddle);
}
