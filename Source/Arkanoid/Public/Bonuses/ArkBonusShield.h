// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "ArkBonusParent.h"
#include "ArkBonusShield.generated.h"

UCLASS()
class ARKANOID_API AArkBonusShield : public AArkBonusParent
{
	GENERATED_BODY()

public:
	AArkBonusShield();

protected:
	virtual void BonusAction(AArkPaddle* Paddle) override;
};
