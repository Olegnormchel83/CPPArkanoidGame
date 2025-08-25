// Olegnormchel. All rights reserved

#include "ArkPC.h"

#include "ArkHUDClass.h"

void AArkPC::ExitButtonPressed()
{
	const auto CurrentHUD = Cast<AArkHUDClass>(GetHUD());
	if (!CurrentHUD) return;

	if (IsPaused())
	{
		SetPause(false);
		CurrentHUD->HidePauseWidget();
	}
	else
	{
		SetPause(true);
		CurrentHUD->ShowPauseWidget();
	}
}

void AArkPC::ShowGameEndMenu(const bool bWinStatus)
{
	const auto CurrentHUD = Cast<AArkHUDClass>(GetHUD());
	if (CurrentHUD)
		CurrentHUD->ShowGameEndWidget(bWinStatus);

	SetPause(true);
}
