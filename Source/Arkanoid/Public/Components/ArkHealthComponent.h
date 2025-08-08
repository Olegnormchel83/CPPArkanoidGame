// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArkHealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ARKANOID_API UArkHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UArkHealthComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	int32 Health = 1;

public:
	/**
	 * Устанавливает количество жизней
	 * @param NewHealth Новое количество жизней
	 */
	UFUNCTION(BlueprintCallable)
	void SetHealth(const int32 NewHealth);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
	void TakeDamage(const int32 Damage = 1);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool IsAlive() const { return Health > 0; }
};
