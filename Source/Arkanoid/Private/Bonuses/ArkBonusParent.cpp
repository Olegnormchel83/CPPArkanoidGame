// Olegnormchel. All rights reserved


#include "Bonuses/ArkBonusParent.h"

#include "ArkPaddle.h"

AArkBonusParent::AArkBonusParent()
{
	PrimaryActorTick.bCanEverTick = true;

	BonusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonusMesh"));
	check(BonusMesh);

	SetRootComponent(BonusMesh);
	BonusMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BonusMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BonusMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AArkBonusParent::BeginPlay()
{
	Super::BeginPlay();

	Direction = Direction.GetSafeNormal();
}

void AArkBonusParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void AArkBonusParent::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!IsValid(OtherActor)) return;
	
	if (auto Paddle = Cast<AArkPaddle>(OtherActor))
	{
		BonusAction(Paddle);
	}
}

void AArkBonusParent::Move(const float DeltaTime)
{
	const FVector Offset = Direction * Speed * DeltaTime;
	AddActorWorldOffset(Offset);
}

void AArkBonusParent::BonusAction(AArkPaddle* Paddle)
{
	Destroy();
}

void AArkBonusParent::InitScale(const FVector& NewScale)
{
	SetActorScale3D(NewScale);
}
