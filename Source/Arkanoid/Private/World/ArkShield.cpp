// Olegnormchel. All rights reserved

#include "ArkShield.h"

#include "Components/BoxComponent.h"

AArkShield::AArkShield()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	check(Box);
	
	SetRootComponent(Box);
	Box->SetBoxExtent(FVector(64.f, 400.f, 64.f));
	Box->SetCollisionResponseToAllChannels(ECR_Block);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	check(StaticMesh);
	
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetAbsolute(false, false, true);
}
