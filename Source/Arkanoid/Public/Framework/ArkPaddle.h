// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"

#include "ArkPaddle.generated.h"

UCLASS()
class ARKANOID_API AArkPaddle : public APawn
{
	GENERATED_BODY()

public:
	AArkPaddle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
