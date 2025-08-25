// Olegnormchel. All rights reserved


#include "ArkHUDClass.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/ArkHUD.h"
#include "Widgets/ArkPauseWidget.h"

void AArkHUDClass::BeginPlay()
{
	Super::BeginPlay();

	if (HudWidgetClass)
	{
		HudWidget = CreateWidget<UArkHUD>(PlayerOwner, HudWidgetClass);
		if (HudWidget)
			HudWidget->AddToViewport();
	}

	ChangeInputMode();
}

void AArkHUDClass::ChangeInputMode(UWidget* Widget)
{
	if (Widget)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(Widget->TakeWidget());
		PlayerOwner->SetInputMode(InputMode);
		PlayerOwner->SetShowMouseCursor(true);
	}
	else
	{
		const FInputModeGameOnly InputMode;
		PlayerOwner->SetInputMode(InputMode);
		PlayerOwner->SetShowMouseCursor(false);
		PlayerOwner->SetPause(false);
	}
}

void AArkHUDClass::ShowPauseWidget()
{
	if (!PauseWidget)
	{
		PauseWidget = CreateWidget<UArkPauseWidget>(PlayerOwner, PauseWidgetClass);
		if (PauseWidget)
		{
			PauseWidget->AddToViewport(99);
			ChangeInputMode(PauseWidget);
			PauseWidget->OnGameResume.AddDynamic(this, &ThisClass::AArkHUDClass::HidePauseWidget);
		}
	}
	else
	{
		PauseWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ChangeInputMode(PauseWidget);
	}
}

void AArkHUDClass::HidePauseWidget()
{
	if (PauseWidget)
	{
		PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
		ChangeInputMode();
	}
}

void AArkHUDClass::ShowGameEndWidget(const bool bWinStatus)
{
	ShowPauseWidget();
	if (PauseWidget)
		PauseWidget->SetWinStatus(bWinStatus);	
}
