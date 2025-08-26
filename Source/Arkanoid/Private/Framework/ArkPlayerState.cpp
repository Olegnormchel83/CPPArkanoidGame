// Olegnormchel. All rights reserved

#include "ArkPlayerState.h"

#include "ArkGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, Log, All);

void AArkPlayerState::ChangePlayerScore(const int32 Amount)
{
	PlayerScore = FMath::Max(PlayerScore + Amount, 0);

	if (const auto Gi = Cast<UArkGameInstance>(GetGameInstance()))
		Gi->SetLevelRecord(UGameplayStatics::GetCurrentLevelName(this), PlayerScore);
	
	OnPlayerScoreChanged.Broadcast(PlayerScore);

	UE_LOG(LogPlayerState, Display, TEXT("PlayerScore = %d"), PlayerScore);
}
