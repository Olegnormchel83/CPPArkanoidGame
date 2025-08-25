// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArkHUD.generated.h"

class AArkGameState;
class AArkPlayerState;
class UTextBlock;

UCLASS()
class ARKANOID_API UArkHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* CurrentScore = nullptr;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	UTextBlock* GameTime = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* ShakeAnimation = nullptr;

	UPROPERTY()
	AArkPlayerState* PlayerState = nullptr;

	UPROPERTY()
	AArkGameState* GameState = nullptr;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void UpdateScore(const int32 NewScore);

	void UpdateTime();
};
