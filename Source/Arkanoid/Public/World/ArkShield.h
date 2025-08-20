// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArkShield.generated.h"

class UBoxComponent;

UCLASS()
class ARKANOID_API AArkShield : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components",
		meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components",
		meta=(AllowPrivateAccess=true))
	UBoxComponent* Box = nullptr;
	
public:
	AArkShield();

};
