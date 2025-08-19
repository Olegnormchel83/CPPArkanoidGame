// Olegnormchel. All rights reserved


#include "World/ArkBlock.h"

#include "ArkBonusParent.h"
#include "ArkPlayerState.h"
#include "Components/ArkHealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "World/ArkBall.h"

AArkBlock::AArkBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject
		<UStaticMeshComponent>(TEXT("StaticMesh"));
	check(StaticMesh);

	SetRootComponent(StaticMesh);

	HealthComponent = CreateDefaultSubobject<UArkHealthComponent>(TEXT("HealthComponent"));
	check(HealthComponent);
}

void AArkBlock::Init(
	const FVector& NewScale,
	const int32 LifeAmount,
	const TSubclassOf<AArkBonusParent>& NewBonusClass)
{
	SetActorScale3D(NewScale);
	BonusClass = NewBonusClass;
	HealthComponent->SetHealth(LifeAmount);
	MaxLife = LifeAmount;
	
	if (HealthMaterials.IsValidIndex(HealthComponent->GetHealth() - 1))
		StaticMesh->SetMaterial(0, HealthMaterials[HealthComponent->GetHealth() - 1]);
}

void AArkBlock::BeginPlay()
{
	Super::BeginPlay();
}

void AArkBlock::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
                          FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (!GetWorld()) return;

	if (const auto Ball = Cast<AArkBall>(Other))
	{
		if (IsValid(HealthComponent))
		{
			HealthComponent->TakeDamage(Ball->GetPower());

			if (!HealthComponent->IsAlive())
			{
				if (BonusClass)
				{
					GetWorld()->SpawnActor<AArkBonusParent>(BonusClass, GetActorLocation(), GetActorRotation());
				}

				if (const auto Pawn = Cast<APawn>(Other->GetOwner()))
				{
					if (auto PlayerState = Cast<AArkPlayerState>(Pawn->GetPlayerState()))
						PlayerState->ChangePlayerScore(ScoreByLife * MaxLife);
				}
				
				Destroy();
			}
			else
			{
				if (HealthMaterials.IsValidIndex(HealthComponent->GetHealth() - 1))
					StaticMesh->SetMaterial(0, HealthMaterials[HealthComponent->GetHealth() - 1]);
			}
		}
	}
}
