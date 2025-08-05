// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArkBall.generated.h"

class UArrowComponent;

UENUM()
enum class EState : uint8
{
	Idle = 0,
	Moving,
};

USTRUCT(BlueprintType)
struct FInitParameters
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Tooltip = "Стартовый размер"))
	float Scale;
	
	UPROPERTY(EditDefaultsOnly, meta = (Tooltip = "Начальная сила"))
	int32 Power;
	
	UPROPERTY(EditDefaultsOnly, meta = (Tooltip = "Начальная скорость"))
	float Speed;

	UPROPERTY(EditDefaultsOnly, meta = (Tooltip = "Максимальная скорость"))
	float MaxSpeed;

	// Default structure contructor
	FInitParameters()
	{
		Scale = 1.0f;
		Power = 1;
		Speed = 500.0f;
		MaxSpeed = 2500.0f;
	}
};

UCLASS()
class ARKANOID_API AArkBall : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ForwardArrow = nullptr;

	int32 Power = 1;
	float Speed = 0.f;
	FVector Direction = FVector::ZeroVector;
	EState State = EState::Idle;
	
public:
	AArkBall();
	
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	FInitParameters InitParameters;

	/**
	 * Функция для обработки движения
	 * @param DeltaTime Время, прошедшее с последнего кадра
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Move(const float DeltaTime);

	/**
	 * Функция для изменения состояния шарика
	 * @param NewState Новый статус
	 */
	void SetBallState(const EState NewState);
};
