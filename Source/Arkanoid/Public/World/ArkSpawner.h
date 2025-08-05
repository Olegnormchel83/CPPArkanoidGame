// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArkSpawner.generated.h"

class UArrowComponent;

UCLASS()
class ARKANOID_API AArkSpawner : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ForwardArrow = nullptr;

	FTimerHandle SpawnActorsTimerHandle;
public:	
	AArkSpawner();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<AActor> SpawnedClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings",
		meta = (ClampMin = "1", UIMin = "1"))
	float SpawnTime = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bLoopSpawn = true;
	
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnActor();
};
