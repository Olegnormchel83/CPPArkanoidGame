// Olegnormchel. All rights reserved

#include "ArkPaddle.h"

#include "ArkBall.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
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

void AArkPaddle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetActorScale3D(DefaultScale);
	BoxCollider->SetBoxExtent(FVector(25.f, 50.f + 20.f / DefaultScale.Y, 25.f));
	const FVector TempScale = FVector(GetActorScale().X, GetActorScale().X, GetActorScale().Z);
	LeftStaticMesh->SetWorldScale3D(TempScale);
	RightStaticMesh->SetWorldScale3D(TempScale);
}

void AArkPaddle::ExitGame()
{
	if (!GetWorld()) return;
	UGameplayStatics::OpenLevel(GetWorld(), "Menu", true);
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
		AddActorWorldOffset(FVector(0.f,CurrentSpeed, 0.f), true);
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

			CurrentBall->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
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
	}
}
