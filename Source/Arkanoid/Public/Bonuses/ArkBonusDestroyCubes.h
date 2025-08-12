// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "ArkBonusParent.h"
#include "ArkBonusDestroyCubes.generated.h"

UCLASS()
class ARKANOID_API AArkBonusDestroyCubes : public AArkBonusParent
{
	GENERATED_BODY()

public:
	AArkBonusDestroyCubes();

protected:
	virtual void BonusAction(AArkPaddle* Paddle) override;
};
