// Olegnormchel. All rights reserved


#include "World/ArkKillZone.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

AArkKillZone::AArkKillZone()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	check(Root);
	SetRootComponent(Root);

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));
	check(ForwardArrow);
	ForwardArrow->SetupAttachment(Root);
	ForwardArrow->SetAbsolute(
	false,
	false,
	true);
	ForwardArrow->SetHiddenInGame(false);

	KillBox = CreateDefaultSubobject<UBoxComponent>(TEXT("KillBox"));
	check(KillBox);
	KillBox->SetupAttachment(Root);
	KillBox->SetBoxExtent(FVector(50.f, 500.f, 50.f));
}

void AArkKillZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor != this)
	{
		OtherActor->Destroy();
	}
}