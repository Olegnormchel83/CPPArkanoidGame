// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArkPC.generated.h"

UCLASS()
class ARKANOID_API AArkPC : public APlayerController
{
	GENERATED_BODY()

public:
	void ExitButtonPressed();

	void ShowGameEndMenu(const bool bWinStatus);
};
