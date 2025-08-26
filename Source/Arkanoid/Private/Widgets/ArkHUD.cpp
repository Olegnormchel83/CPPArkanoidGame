// Olegnormchel. All rights reserved

#include "Widgets/ArkHUD.h"

#include "ArkGameInstance.h"
#include "ArkGameState.h"
#include "ArkPlayerState.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UArkHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (GetOwningPlayer())
	{
		PlayerState = GetOwningPlayer()->GetPlayerState<AArkPlayerState>();
		if (PlayerState)
			PlayerState->OnPlayerScoreChanged.AddDynamic(this, &ThisClass::UpdateScore);
		
	}

	if (GetWorld())
		GameState = Cast<AArkGameState>(GetWorld()->GetGameState());

	if (CurrentScore)
	{
		const FString DefaultScoreText = FString::Printf(TEXT("СЧЁТ: 000"));
		CurrentScore->SetText(FText::FromString(DefaultScoreText));
	}

	UpdateLevelRecord();
}

void UArkHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateTime();
}

void UArkHUD::UpdateScore(const int32 NewScore)
{
	if (CurrentScore)
	{
		const FString ScoreString = FString::Printf(TEXT("СЧЁТ: %03d"), NewScore);
		CurrentScore->SetText(FText::FromString(ScoreString));

		if (ShakeAnimation)
		{
			PlayAnimation(
				ShakeAnimation,
				0.f,
				1,
				EUMGSequencePlayMode::Forward,
				1.f
				);
		}
	}

	UpdateLevelRecord();
}

void UArkHUD::UpdateTime()
{
	if (GameTime && GameState)
	{
		int32 Minutes = 0;
		int32 Seconds= 0;
		int32 Milliseconds = 0;
		GameState->GetGameTime(Minutes, Seconds, Milliseconds);

		const FString TimeString = FString::Printf(TEXT("%02d : %02d : %03d"), Minutes, Seconds, Milliseconds);
		GameTime->SetText(FText::FromString(TimeString));
	}
}

void UArkHUD::UpdateLevelRecord()
{
	if (LevelRecord)
	{
		if (const auto Gi = Cast<UArkGameInstance>(GetGameInstance()))
		{
			const int32 CurrentRecord = Gi->GetLevelRecord(UGameplayStatics::GetCurrentLevelName(this, true));
			const FString ScoreText = FString::Printf(TEXT("РЕКОРД: %03d"), CurrentRecord);
			LevelRecord->SetText(FText::FromString(*ScoreText));
		}
	}
}
