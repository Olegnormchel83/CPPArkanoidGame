// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArkBlock.generated.h"

class UArkHealthComponent;

UCLASS()
class ARKANOID_API AArkBlock : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
			meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
			meta = (AllowPrivateAccess = "true"))
	UArkHealthComponent* HealthComponent = nullptr;
	
	TSubclassOf<AActor> BonusClass = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AArkBlock();

	void Init(
		const FVector& NewScale,
		const int32 LifeAmount,
		const TSubclassOf<AActor>& NewBonusClass = nullptr);
	
protected:

	virtual void BeginPlay() override;
	
	virtual void NotifyHit(
		UPrimitiveComponent* MyComp,
		AActor* Other,
		UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TArray<UMaterialInterface*> HealtMaterials;
};
