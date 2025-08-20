// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArkBlock.generated.h"

class AArkBonusParent;
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
	
	TSubclassOf<AArkBonusParent> BonusClass = nullptr;

	int32 MaxLife = 1;
	
public:	
	AArkBlock();

	void Init(
		const FVector& NewScale,
		const int32 LifeAmount,
		const TSubclassOf<AArkBonusParent>& NewBonusClass = nullptr);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 ScoreByLife = 25;
	
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
	TArray<UMaterialInterface*> HealthMaterials;
};
