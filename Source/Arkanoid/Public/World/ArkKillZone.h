// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArkKillZone.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class ARKANOID_API AArkKillZone : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
	meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ForwardArrow = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UBoxComponent* KillBox = nullptr;
	
public:	
	AArkKillZone();

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
