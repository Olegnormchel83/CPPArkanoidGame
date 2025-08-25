// Olegnormchel. All rights reserved

#include "ArkPaddle.h"

#include "ArkBall.h"
#include "ArkGameMode.h"
#include "ArkPC.h"
#include "ArkShield.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

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

	TopCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopCamera"));
	check(TopCamera);
	TopCamera->SetupAttachment(GetRootComponent());
	TopCamera->bUsePawnControlRotation = false;
	TopCamera->SetRelativeLocation(FVector(1550.f, 0.f, 4160.f));
	TopCamera->SetRelativeRotation(FRotator(0, -90.f, 0));

	POVCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("POVCamera"));
	check(POVCamera);
	POVCamera->SetupAttachment(StaticMesh);
	POVCamera->SetAbsolute(false, false, true);
}

void AArkPaddle::BeginPlay()
{
	Super::BeginPlay();

	if (const auto* PlayerController = Cast<APlayerController>(Controller))
	{
		const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
			(PlayerController->GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	SpawnBall();
	SpawnBallLives();
}

void AArkPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(EscapeAction, ETriggerEvent::Started, this, &AArkPaddle::ExitGame);
		EnhancedInputComponent->BindAction(SpawnBallAction, ETriggerEvent::Started, this, &AArkPaddle::StartGame);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AArkPaddle::Move);
	}
}


void AArkPaddle::SetDefaultSize()
{
	SetActorScale3D(DefaultScale);
	BoxCollider->SetBoxExtent(FVector(25.f, 50 + 20.f / DefaultScale.Y, 25.f));
	BonusSizeTimer.Invalidate();
}

void AArkPaddle::SetDefaultControl()
{
	bInvertControl = false;
	InvertControlTimer.Invalidate();
}

void AArkPaddle::OnShieldDestroyed()
{
	bShieldEnabled = false;
	ShieldTimer.Invalidate();
}

void AArkPaddle::SetDefaultCameraRotation()
{
	if (!TopCamera) return;

	const auto NewRotation = TopCamera->GetRelativeRotation() -
		FRotator(0.f, 180.f, 0);
	TopCamera->SetRelativeRotation(NewRotation);

	RotateCameraTimer.Invalidate();
}

void AArkPaddle::SetTopCamera()
{
	if (!TopCamera) return;

	POVCamera->SetActive(false);
	TopCamera->SetActive(true);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->SetViewTargetWithBlend(this, 0.5f);
	}

	POVCameraTimer.Invalidate();
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

void AArkPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TopCamera && TopCamera->IsActive())
	{
		TopCamera->SetWorldLocation(FVector(1550.f, 0.f, 4160.f));
	}
}

void AArkPaddle::ExitGame()
{
	if (!GetWorld()) return;
	//UGameplayStatics::OpenLevel(GetWorld(), "Menu", true);

	if (const auto PC = Cast<AArkPC>(Controller))
	{
		PC->ExitButtonPressed();
	}
}

void AArkPaddle::StartGame()
{
	if (!GetWorld()) return;

	if (CurrentBall)
	{
		CurrentBall->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentBall->SetBallState(EState::Moving);
	}
}

void AArkPaddle::Move(const FInputActionValue& Value)
{
	if (!GetWorld()) return;

	const FVector2D AxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const float CurrentSpeed = AxisVector.X * Speed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
		AddActorWorldOffset(FVector(
			                    0.f,
			                    bInvertControl ? -CurrentSpeed : CurrentSpeed,
			                    0.f), true);
	}
}

void AArkPaddle::SpawnBall()
{
	if (!GetWorld()) return;

	if (BallClass && !CurrentBall)
	{
		const FVector SpawnLocation = Arrow->GetComponentLocation();
		const FRotator SpawnRotation = Arrow->GetComponentRotation();

		CurrentBall = GetWorld()->SpawnActor<AArkBall>(BallClass, SpawnLocation, SpawnRotation);
		if (CurrentBall)
		{
			CurrentBall->SetOwner(this);
			CurrentBall->SetBallState(EState::Idle);
			CurrentBall->OnDeadEvent.AddDynamic(this, &AArkPaddle::BallIsDead);

			//CurrentBall->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			CurrentBall->AttachToComponent(Arrow, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void AArkPaddle::BallIsDead()
{
	CurrentBall = nullptr;
	Lives = FMath::Max(Lives - 1, 0);

	if (Lives)
	{
		SpawnBall();
		BallLives[Lives - 1]->DestroyComponent();
		BallLives.RemoveAt(Lives - 1);
		UpdateBallLivesLocation();
	}
	else
	{
		if (const auto GM = Cast<AArkGameMode>(GetWorld()->GetAuthGameMode()))
			GM->GameEnded(false);
	}
}

void AArkPaddle::SpawnBallLives()
{
	if (!LivesMesh) return;

	for (auto LiveBall : BallLives)
	{
		LiveBall->DestroyComponent();
	}
	BallLives.Empty();

	for (int8 i = 0; i < Lives - 1; ++i)
	{
		auto* NewMeshComp = NewObject<UStaticMeshComponent>
			(this, *FString::Printf(TEXT("Lives %d"), i + 1));

		if (NewMeshComp)
		{
			NewMeshComp->SetStaticMesh(LivesMesh);
			NewMeshComp->SetAbsolute(false, false, true);
			NewMeshComp->SetWorldScale3D(FVector(0.4f));
			NewMeshComp->SetupAttachment(GetRootComponent());
			NewMeshComp->RegisterComponent();

			BallLives.Add(NewMeshComp);
			UpdateBallLivesLocation();
		}
	}
}

void AArkPaddle::UpdateBallLivesLocation()
{
	constexpr float BallSpacing = 30.f; // Расстояние между шариками 
	const int8 NumBalls = BallLives.Num();

	const float TotalWidth = (NumBalls - 1) * BallSpacing; // Общая ширина расположения шариков
	const float StartOffset = -TotalWidth / 2; // Начальное смещение для первого шарика

	for (int8 i = 0; i < NumBalls; ++i)
	{
		const float Offset = StartOffset + i * BallSpacing;
		if (IsValid(BallLives[i]))
		{
			BallLives[i]->SetRelativeLocation(FVector(-100.f, Offset, 0.f));
		}
	}
}

// Работа с бонусами

void AArkPaddle::BonusChangeSize(const float AdditionalSize, const float BonusTime)
{
	if (AdditionalSize == 0 || BonusTime == 0) return;
	if (!GetWorld()) return;

	if (!GetWorld()->GetTimerManager().IsTimerActive(BonusSizeTimer))
	{
		FVector TempScale = GetActorScale3D();
		TempScale.Y += TempScale.Y * AdditionalSize;
		SetActorScale3D(TempScale);
		BoxCollider->SetBoxExtent(FVector(25.f, 50.f + 20.f / TempScale.Y, 25.f));
	}

	GetWorld()->GetTimerManager().SetTimer(
		BonusSizeTimer,
		this,
		&ThisClass::SetDefaultSize,
		BonusTime,
		false
	);
}

void AArkPaddle::BonusChangeLives(const int32 Amount)
{
	Lives += Amount;
	SpawnBallLives();
}

void AArkPaddle::BonusChangeBallSpeed(const float Amount) const
{
	if (!IsValid(CurrentBall)) return;

	CurrentBall->ChangeSpeed(Amount);
}

void AArkPaddle::BonusChangeBallPower(const int32 Amount, const float BonusTime) const
{
	if (!IsValid(CurrentBall)) return;

	CurrentBall->ChangePower(Amount, BonusTime);
}

void AArkPaddle::BonusInvertControl(const int32 Amount, const float BonusTime)
{
	if (!GetWorld() || BonusTime == 0) return;

	if (!GetWorld()->GetTimerManager().IsTimerActive(InvertControlTimer))
	{
		bInvertControl = true;
	}

	GetWorld()->GetTimerManager().SetTimer(
		InvertControlTimer,
		this,
		&ThisClass::SetDefaultControl,
		BonusTime,
		false
	);
}

void AArkPaddle::BonusSpawnShield(const float BonusTime)
{
	if (!GetWorld() || BonusTime == 0 || bShieldEnabled) return;

	const FTransform ShieldTransform = FTransform(
		FRotator::ZeroRotator,
		ShieldSpawnLocation,
		FVector::OneVector
	);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto Shield = GetWorld()->SpawnActor<AArkShield>(ShieldClass, ShieldTransform, SpawnParameters);
	if (Shield)
	{
		bShieldEnabled = true;
		Shield->SetLifeSpan(BonusTime);

		GetWorld()->GetTimerManager().SetTimer(
			ShieldTimer,
			this,
			&ThisClass::OnShieldDestroyed,
			BonusTime,
			false
		);
	}
}

void AArkPaddle::BonusRotateCamera(const float BonusTime)
{
	if (!GetWorld() || BonusTime == 0 || !TopCamera) return;

	if (!GetWorld()->GetTimerManager().IsTimerActive(RotateCameraTimer))
	{
		const auto NewRotation = TopCamera->GetRelativeRotation() +
			FRotator(0.f, 180.f, 0.f);
		TopCamera->SetRelativeRotation(NewRotation);
	}

	GetWorld()->GetTimerManager().SetTimer(
		RotateCameraTimer,
		this,
		&ThisClass::SetDefaultCameraRotation,
		BonusTime,
		false
	);
}

void AArkPaddle::BonusSetPOVCamera(const float BonusTime)
{
	if (!GetWorld() || BonusTime == 0 || !POVCamera) return;

	if (!GetWorld()->GetTimerManager().IsTimerActive(POVCameraTimer))
	{
		TopCamera->SetActive(false);
		POVCamera->SetActive(true);

		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			PC->SetViewTargetWithBlend(this, 0.5f);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(
		POVCameraTimer,
		this,
		&ThisClass::SetTopCamera,
		BonusTime,
		false
	);
}
