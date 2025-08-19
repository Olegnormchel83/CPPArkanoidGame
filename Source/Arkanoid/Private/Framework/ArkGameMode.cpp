// Olegnormchel. All rights reserved

#include "ArkGameMode.h"

#include "ArkGameState.h"
#include "ArkPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogArkGameMode, Log, All);

AArkGameMode::AArkGameMode()
{
	GameStateClass = AArkGameState::StaticClass();
	PlayerStateClass = AArkPlayerState::StaticClass();
}

void AArkGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameStarted();
}

void AArkGameMode::GameStarted()
{
	auto ArkGameState = Cast<AArkGameState>(GameState);
	if (!ArkGameState) return;

	ArkGameState->StartGame();
}

void AArkGameMode::GameEnded()
{
	auto ArkGameState = Cast<AArkGameState>(GameState);
	if (!ArkGameState) return;

	ArkGameState->StopGame();

	UE_LOG(LogArkGameMode, Warning, TEXT("GameEnded"));
}
