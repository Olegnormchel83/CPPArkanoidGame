// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArkPauseWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameResume);

class UButton;
class UTextBlock;

UCLASS()
class ARKANOID_API UArkPauseWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* StatusText = nullptr;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UButton* ResumeButton = nullptr;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UButton* RestartButton = nullptr;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UButton* MenuButton = nullptr;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void BackToMenu();

public:
	UPROPERTY(BlueprintAssignable, Category = "PauseWidget")
	FOnGameResume OnGameResume;

	void SetWinStatus(const bool bWinStatus);
};
