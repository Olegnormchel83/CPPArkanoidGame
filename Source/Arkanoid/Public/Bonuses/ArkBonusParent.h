// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArkBonusParent.generated.h"

class AArkPaddle;
class UStaticMeshComponent;

UCLASS(Blueprintable, Abstract)
class ARKANOID_API AArkBonusParent : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BonusMesh = nullptr;
	
public:	
	AArkBonusParent();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void Move(const float DeltaTime);

	virtual void BonusAction(AArkPaddle* Paddle);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings",
		meta = (ToolTip = "Направление движения"))
	FVector Direction = FVector(-1.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings",
		meta = (ToolTip = "Длительность"))
	float Duration = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings",
		meta = (ToolTip = "Скорость падения"))
	float Speed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float Value = 0.5f;

	void InitScale(const FVector& NewScale);
};
