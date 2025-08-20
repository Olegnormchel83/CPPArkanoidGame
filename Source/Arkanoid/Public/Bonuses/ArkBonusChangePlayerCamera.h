// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "ArkBonusParent.h"
#include "ArkBonusChangePlayerCamera.generated.h"

UCLASS()
class ARKANOID_API AArkBonusChangePlayerCamera : public AArkBonusParent
{
	GENERATED_BODY()

public:
	AArkBonusChangePlayerCamera();

protected:
	virtual void BonusAction(AArkPaddle* Paddle) override;
};
