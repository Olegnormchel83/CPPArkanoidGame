// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ArkGameState.generated.h"

UCLASS()
class ARKANOID_API AArkGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	float GameTime = 0.f;

	bool bGameStarted = false;

protected:
	virtual void Tick(float DeltaTime) override;

public:
	AArkGameState();

	void StartGame();
	
	void StopGame();

	UFUNCTION(BlueprintPure, Category = "GameState")
	void GetGameTime(int32& Minutes, int32& Seconds, int32& Milliseconds) const;
};
