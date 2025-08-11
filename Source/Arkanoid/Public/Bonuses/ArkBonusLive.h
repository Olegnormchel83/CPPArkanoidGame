// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Bonuses/ArkBonusParent.h"
#include "ArkBonusLive.generated.h"

UCLASS()
class ARKANOID_API AArkBonusLive : public AArkBonusParent
{
	GENERATED_BODY()

public:
	AArkBonusLive();

protected:
	virtual void BonusAction(AArkPaddle* Paddle) override;
};
