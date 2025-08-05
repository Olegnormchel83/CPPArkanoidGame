// Olegnormchel. All rights reserved


#include "World/ArkSpawner.h"
#include "Components/ArrowComponent.h"

AArkSpawner::AArkSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	check(Root);
	SetRootComponent(Root);

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));
	check(ForwardArrow);
	ForwardArrow->SetupAttachment(GetRootComponent());
	ForwardArrow->SetAbsolute(
		false,
		false,
		true);
}

void AArkSpawner::BeginPlay()
{
	Super::BeginPlay();

	// Единичное/цикличное создание акторов указанного класса раз в SpawnTime секунд
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			SpawnActorsTimerHandle,
			this,
			&ThisClass::SpawnActor,
			SpawnTime,
			bLoopSpawn,
			0.f);
	}
}

void AArkSpawner::SpawnActor()
{
	if (!GetWorld()) return;
	if (!SpawnedClass) return;

	GetWorld()->SpawnActor<AActor>(
		SpawnedClass,
		ForwardArrow->GetComponentLocation(),
		ForwardArrow->GetComponentRotation());
}
