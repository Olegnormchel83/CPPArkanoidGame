// Olegnormchel. All rights reserved

#include "ArkBonusChangePlayerCamera.h"

#include "ArkPaddle.h"

AArkBonusChangePlayerCamera::AArkBonusChangePlayerCamera()
{
	Duration = 4.f;
}

void AArkBonusChangePlayerCamera::BonusAction(AArkPaddle* Paddle)
{
	if (!Paddle) return;

	Paddle->BonusSetPOVCamera(Duration);
	
	Super::BonusAction(Paddle);
}




