// Olegnormchel. All rights reserved


#include "Bonuses/ArkBonusPaddleSize.h"

#include "ArkPaddle.h"

AArkBonusPaddleSize::AArkBonusPaddleSize()
{
	Duration = 10.0f;
}

void AArkBonusPaddleSize::BonusAction(AArkPaddle* Paddle)
{
	if (!Paddle) return;
	
	Paddle->BonusChangeSize(Value, Duration);
	
	Super::BonusAction(Paddle);
}
