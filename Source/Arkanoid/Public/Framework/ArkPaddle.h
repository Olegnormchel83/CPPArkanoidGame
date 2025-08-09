// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"

#include "ArkPaddle.generated.h"

class AArkBall;
class UArrowComponent;
class UBoxComponent;

UCLASS()
class ARKANOID_API AArkPaddle : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftStaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightStaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UArrowComponent* Arrow = nullptr;

	UPROPERTY()
	AArkBall* CurrentBall = nullptr;
	
public:
	AArkPaddle();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Settings | Game",
		meta = (ToolTip = "Класс мяча для спауна"))
	TSubclassOf<AArkBall> BallClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Settings | Game",
		meta = (ToolTip = "Размер каретки (по умолчанию)"))
	FVector DefaultScale = FVector(0.4f, 2.4f, 0.5f);

	UPROPERTY(EditDefaultsOnly, Category = "Settings | Game",
		meta = (ToolTip = "Жизни"))
	int32 Lives = 3;
	
	UPROPERTY(EditDefaultsOnly, Category = "Settings | Game",
		meta = (ToolTip = "Скорость каретки"))
	float Speed = 2000.f;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
