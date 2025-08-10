// Olegnormchel. All rights reserved


#include "World/ArkBall.h"
#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogArkBall, All, All);

AArkBall::AArkBall()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	check(StaticMesh);

	SetRootComponent(StaticMesh);

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));
	check(ForwardArrow);
	ForwardArrow->SetupAttachment(GetRootComponent());
}

void AArkBall::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetActorScale3D(FVector(InitParameters.Scale));
	Power = InitParameters.Power;
	Speed = InitParameters.Speed;
}

void AArkBall::BeginPlay()
{
	Super::BeginPlay();

	Direction = GetActorForwardVector().GetSafeNormal();
	SetBallState(EState::Moving);
}

void AArkBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (State)
	{
	case EState::Idle:
		break;
	case EState::Moving:
		Move(DeltaTime);
		break;
	default:
		UE_LOG(LogArkBall, Warning, TEXT("Unknown state."));
		break;
	}
}

void AArkBall::Destroyed()
{
	OnDeadEvent.Broadcast();
	
	Super::Destroyed();
}

void AArkBall::Move(const float DeltaTime)
{
	const FVector Offset = Direction * Speed * DeltaTime;
	FHitResult Hit;
	AddActorWorldOffset(Offset, true, &Hit);

	if (Hit.bBlockingHit)
	{
		Direction = Direction - 2 * (FVector::DotProduct(Direction, Hit.Normal)) * Hit.Normal;
		Direction.Z = 0.f;
		Direction = Direction.GetSafeNormal();

		if (Speed < InitParameters.MaxSpeed)
		{
			Speed += InitParameters.Speed * 0.1f;
			Speed = FMath::Min(Speed, InitParameters.MaxSpeed);
			UE_LOG(LogArkBall, Warning, TEXT("Updated ball speed: %.1f"), Speed);
		}
	}
}

void AArkBall::SetBallState(const EState NewState)
{
	State = NewState;
}
