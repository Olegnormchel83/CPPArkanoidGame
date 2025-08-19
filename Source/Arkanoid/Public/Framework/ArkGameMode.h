// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkGameMode.generated.h"

UCLASS()
class ARKANOID_API AArkGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AArkGameMode();
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category="GameMode")
	void GameStarted();

	UFUNCTION(BlueprintCallable, Category="GameMode")
	void GameEnded();
};
