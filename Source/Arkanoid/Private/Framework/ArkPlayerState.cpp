// Olegnormchel. All rights reserved

#include "ArkPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, Log, All);

void AArkPlayerState::ChangePlayerScore(const int32 Amount)
{
	PlayerScore = FMath::Max(PlayerScore + Amount, 0);
	OnPlayerScoreChanged.Broadcast(PlayerScore);

	UE_LOG(LogPlayerState, Display, TEXT("PlayerScore = %d"), PlayerScore);
}
