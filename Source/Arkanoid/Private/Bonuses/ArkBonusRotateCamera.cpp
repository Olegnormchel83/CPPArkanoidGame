// Olegnormchel. All rights reserved


#include "ArkBonusRotateCamera.h"

#include "ArkPaddle.h"


// Sets default values
AArkBonusRotateCamera::AArkBonusRotateCamera()
{
	Duration = 5.f;
}

void AArkBonusRotateCamera::BonusAction(AArkPaddle* Paddle)
{
	if (!Paddle) return;

	Paddle->BonusRotateCamera(Duration);
	
	Super::BonusAction(Paddle);
}


