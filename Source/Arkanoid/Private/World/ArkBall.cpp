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
	if (StaticMesh)
	{
		DefaultMaterial = StaticMesh->GetMaterial(0);
	}
	UpdateMaterial();
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
		}
	}
}

void AArkBall::SetBallState(const EState NewState)
{
	State = NewState;
}

// Работа с бонусами

void AArkBall::UpdateMaterial()
{
	if (!StaticMesh) return;

	if (Power > 1)
	{
		if (PowerMaterial)
		{
			StaticMesh->SetMaterial(0, PowerMaterial);
		}
	}
	else
	{
		StaticMesh->SetMaterial(0, DefaultMaterial);
	}
}

void AArkBall::ChangeSpeed(const float Amount)
{
	if (Amount < 0)
	{
		Speed = FMath::Min(Speed - Speed * Amount, InitParameters.Speed);
	}
	else if (Amount > 0)
	{
		Speed = FMath::Max(Speed + Speed * Amount, InitParameters.MaxSpeed);
	}
}

void AArkBall::ChangePower(const int32 Amount, const float BonusTime)
{
	if (!GetWorld()) return;

	if (Amount != 0 && BonusTime > 0)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(BallPowerTimer))
		{
			Power = FMath::Max(Power + Amount, 1);
			UpdateMaterial();
		}

		GetWorld()->GetTimerManager().SetTimer(
			BallPowerTimer,
			this,
			&ThisClass::ResetBallPower,
			BonusTime,
			false
		);
	}
}

void AArkBall::ResetBallPower()
{
	Power = InitParameters.Power;
	UpdateMaterial();
}
