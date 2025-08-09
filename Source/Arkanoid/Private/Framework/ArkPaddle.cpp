// Olegnormchel. All rights reserved

#include "ArkPaddle.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

AArkPaddle::AArkPaddle()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	check(BoxCollider);

	SetRootComponent(BoxCollider);
	BoxCollider->SetBoxExtent(FVector(25.f, 50.f, 25.f));
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Block);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	check(StaticMesh);
	StaticMesh->SetupAttachment(GetRootComponent());

	LeftStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftStaticMesh"));
	check(LeftStaticMesh);
	LeftStaticMesh->SetupAttachment(StaticMesh);
	LeftStaticMesh->SetRelativeLocation(FVector(0.f, -50.f, 0.f));
	LeftStaticMesh->SetAbsolute(false, false, true);

	RightStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightStaticMesh"));
	check(RightStaticMesh);
	RightStaticMesh->SetupAttachment(StaticMesh);
	RightStaticMesh->SetRelativeLocation(FVector(0.f, 50.f, 0.f));
	RightStaticMesh->SetAbsolute(false, false, true);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	check(Arrow);
	Arrow->SetupAttachment(StaticMesh);
	Arrow->SetRelativeLocation(FVector(150.f, 0.f, 0.f));
	Arrow->SetAbsolute(false, false, true);
}

void AArkPaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArkPaddle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetActorScale3D(DefaultScale);
	BoxCollider->SetBoxExtent(FVector(25.f, 50.f + 20.f / DefaultScale.Y, 25.f));
	const FVector TempScale = FVector(GetActorScale().X, GetActorScale().X, GetActorScale().Z);
	LeftStaticMesh->SetWorldScale3D(TempScale);
	RightStaticMesh->SetWorldScale3D(TempScale);
}

void AArkPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

