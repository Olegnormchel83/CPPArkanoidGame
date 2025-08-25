// Olegnormchel. All rights reserved

#include "Widgets/ArkPauseWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UArkPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
		ResumeButton->OnReleased.AddDynamic(this, &ThisClass::ResumeGame);

	if (RestartButton)
		RestartButton->OnReleased.AddDynamic(this, &ThisClass::RestartGame);

	if (MenuButton)
		MenuButton->OnReleased.AddDynamic(this, &ThisClass::BackToMenu);
}

void UArkPauseWidget::ResumeGame()
{
	OnGameResume.Broadcast();
}

void UArkPauseWidget::RestartGame()
{
	if (!GetWorld()) return;
	
	const auto LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}

void UArkPauseWidget::BackToMenu()
{
	if (!GetWorld()) return;
	
	UGameplayStatics::OpenLevel(GetWorld(), FName("Menu"));
}

void UArkPauseWidget::SetWinStatus(const bool bWinStatus)
{
	if (!StatusText) return;

	if (ResumeButton)
	{
		ResumeButton->SetIsEnabled(false);
		ResumeButton->SetVisibility(ESlateVisibility::Hidden);
	}

	if (bWinStatus)
	{
		StatusText->SetText(FText::FromString(TEXT("ПОБЕДА!")));
		StatusText->SetColorAndOpacity(FColor::Green);
	}
	else
	{
		StatusText->SetText(FText::FromString(TEXT("ПОРАЖЕНИЕ!")));
		StatusText->SetColorAndOpacity(FColor::Red);
	}
}
