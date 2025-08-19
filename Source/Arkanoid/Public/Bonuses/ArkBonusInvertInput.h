// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Bonuses/ArkBonusParent.h"
#include "ArkBonusInvertInput.generated.h"

UCLASS()
class ARKANOID_API AArkBonusInvertInput : public AArkBonusParent
{
	GENERATED_BODY()

public:
	AArkBonusInvertInput();

protected:
	virtual void BonusAction(AArkPaddle* Paddle) override;
};
