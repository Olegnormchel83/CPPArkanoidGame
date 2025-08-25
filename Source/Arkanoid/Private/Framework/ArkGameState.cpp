// Olegnormchel. All rights reserved

#include "ArkGameState.h"

AArkGameState::AArkGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AArkGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGameStarted)
	{
		GameTime += DeltaTime;
	}
}

void AArkGameState::StartGame()
{
	bGameStarted = true;
}

void AArkGameState::StopGame()
{
	bGameStarted = false;
}

void AArkGameState::GetGameTime(int32& Minutes, int32& Seconds, int32& Milliseconds) const
{
	Minutes = static_cast<int32>(GameTime) / 60;
	Seconds = static_cast<int32>(GameTime) % 60;
	Milliseconds = static_cast<int32>((GameTime - FMath::Floor(GameTime)) * 1000);
}
