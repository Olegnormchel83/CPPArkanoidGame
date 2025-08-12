// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "ArkBonusParent.h"
#include "ArkBonusBallPower.generated.h"

UCLASS()
class ARKANOID_API AArkBonusBallPower : public AArkBonusParent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArkBonusBallPower();

protected:
	virtual void BonusAction(AArkPaddle* Paddle) override;
};
