// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Bonuses/ArkBonusParent.h"
#include "ArkBonusPaddleSize.generated.h"

UCLASS()
class ARKANOID_API AArkBonusPaddleSize : public AArkBonusParent
{
	GENERATED_BODY()

public:
	AArkBonusPaddleSize();

protected:
	virtual void BonusAction(AArkPaddle* Paddle) override;
};
