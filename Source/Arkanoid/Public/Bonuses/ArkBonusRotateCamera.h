// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "ArkBonusParent.h"
#include "ArkBonusRotateCamera.generated.h"

UCLASS()
class ARKANOID_API AArkBonusRotateCamera : public AArkBonusParent
{
	GENERATED_BODY()

public:
	AArkBonusRotateCamera();

protected:
	virtual void BonusAction(AArkPaddle* Paddle) override;
};
