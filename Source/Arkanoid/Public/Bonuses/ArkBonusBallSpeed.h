// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Bonuses/ArkBonusParent.h"
#include "ArkBonusBallSpeed.generated.h"

UCLASS()
class ARKANOID_API AArkBonusBallSpeed : public AArkBonusParent
{
	GENERATED_BODY()

public:
	AArkBonusBallSpeed();

protected:
	virtual void BonusAction(AArkPaddle* Paddle) override;
};
