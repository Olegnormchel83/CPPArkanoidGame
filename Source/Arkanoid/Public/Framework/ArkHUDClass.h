// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ArkHUDClass.generated.h"

class UWidget;
class UArkPauseWidget;
class UArkHUD;

UCLASS()
class ARKANOID_API AArkHUDClass : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UArkHUD* HudWidget = nullptr;

	UPROPERTY()
	UArkPauseWidget* PauseWidget = nullptr;

	void ChangeInputMode(UWidget* Widget = nullptr);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<UArkHUD> HudWidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<UArkPauseWidget> PauseWidgetClass = nullptr;

	void ShowPauseWidget();

	UFUNCTION()
	void HidePauseWidget();

	void ShowGameEndWidget(const bool bWinStatus);
};
