// Olegnormchel. All rights reserved


#include "Bonuses/ArkBonusInvertInput.h"

#include "ArkPaddle.h"

AArkBonusInvertInput::AArkBonusInvertInput()
{
	Duration = 7.f;
}

void AArkBonusInvertInput::BonusAction(AArkPaddle* Paddle)
{
	if (!Paddle) return;

	Paddle->BonusInvertControl(-1, Duration);
	
	Super::BonusAction(Paddle);
}
