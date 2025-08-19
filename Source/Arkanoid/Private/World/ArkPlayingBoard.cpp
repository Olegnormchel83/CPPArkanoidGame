// Olegnormchel. All rights reserved


#include "World/ArkPlayingBoard.h"

#include "ArkBonusParent.h"
#include "ArkGameMode.h"
#include "CollisionShape.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/ArkBlock.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayingBoard, Log, All);

AArkPlayingBoard::AArkPlayingBoard()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	check(SceneRoot);

	SetRootComponent(SceneRoot);
}

void AArkPlayingBoard::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ClearPreviewComponents();
	CreatePreviewComponents();
}

void AArkPlayingBoard::CreatePreviewComponents()
{
	if (GridSizeX <= 0 || GridSizeY <= 0)
	{
		UE_LOG(LogPlayingBoard, Error, TEXT("Grid size must be positive"));
		return;
	}

	const float BlockWidth = BlockScale.X * 100.f;
	const float BlockHeight = BlockScale.Y * 100.f;
	const float BlockDepth = BlockScale.Z * 100.f;

	const float TotalWidth = GridSizeX * BlockWidth + (GridSizeX - 1) * SpacingX;
	const float TotalHeight = GridSizeY * BlockHeight + (GridSizeY - 1) * SpacingY;

	const FVector CenterOffset = FVector(
		(TotalWidth - BlockWidth) / 2,
		(TotalHeight - BlockHeight) / 2,
		0.f);

	const FTransform ActorTransform = GetActorTransform();

	for (int32 x = 0; x < GridSizeX; x++)
	{
		for (int32 y = 0; y < GridSizeY; y++)
		{
			const float XOffset = x * (BlockWidth + SpacingX);
			const float YOffset = y * (BlockHeight + SpacingY);
			const FVector PreviewLocation = FVector(XOffset, YOffset, 0.0f) - CenterOffset;
			const FVector WorldPreviewLocation = ActorTransform.TransformPosition(PreviewLocation);

			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(this);

			const FVector BoxExtents = FVector(BlockWidth * 0.5f, BlockHeight * 0.5f, BlockDepth * 0.5f);

			const bool bIsBlocked = GetWorld()->OverlapBlockingTestByChannel(
				WorldPreviewLocation,
				ActorTransform.GetRotation(),
				ECC_Visibility,
				FCollisionShape::MakeBox(BoxExtents),
				CollisionParams
			);

			if (bIsBlocked)
			{
				// Визуализация области проверки
				DrawDebugBox(
					GetWorld(),
					WorldPreviewLocation,
					BoxExtents,
					ActorTransform.GetRotation(),
					FColor::Red,
					false,
					2.f
				);
				continue;
			}
			else
			{
				// Создаем PreviewMeshComponent и настраиваем его
				UStaticMeshComponent* PreviewMeshComponent = NewObject<UStaticMeshComponent>(this);
				PreviewMeshComponent->SetStaticMesh(PreviewMesh);
				PreviewMeshComponent->AttachToComponent(GetRootComponent(),
				                                        FAttachmentTransformRules::KeepRelativeTransform);
				PreviewMeshComponent->SetRelativeScale3D(BlockScale);
				PreviewMeshComponent->SetRelativeLocation(PreviewLocation);
				PreviewMeshComponent->RegisterComponent();
				PreviewComponents.Add(PreviewMeshComponent);
			}
		}
	}
}

void AArkPlayingBoard::ClearPreviewComponents()
{
	for (auto* PreviewComponent : PreviewComponents)
	{
		if (PreviewComponent)
		{
			PreviewComponent->DestroyComponent();
		}
	}
	PreviewComponents.Empty();
}

void AArkPlayingBoard::SpawnBlockActors()
{
	for (const auto* PreviewComponent : PreviewComponents)
	{
		if (PreviewComponent)
		{
			const FTransform SpawnTransform = PreviewComponent->GetComponentTransform();
			if (auto CurrentBlock = GetWorld()->SpawnActor<AArkBlock>(BlockClassForSpawn, SpawnTransform))
			{
				const int32 Health = UKismetMathLibrary::RandomBoolWithWeight(GameDifficulty) ? 2 : 1;

				const auto BonusClass =
					UKismetMathLibrary::RandomBoolWithWeight(BonusChance) ? GetBonusClass() : nullptr;

				CurrentBlock->Init(BlockScale, Health, BonusClass);

				CurrentBlock->AttachToComponent(
					GetRootComponent(),
					FAttachmentTransformRules::KeepWorldTransform);
				CurrentBlock->OnDestroyed.AddDynamic(this, &ThisClass::OnBlockDestroyed);
				BlockActors.Add(CurrentBlock);
			}
		}
	}
}

void AArkPlayingBoard::OnBlockDestroyed(AActor* DestroyedBlock)
{
	BlockActors.Remove(Cast<AArkBlock>(DestroyedBlock));

	if (BlockActors.Num() == 0)
	{
		if (const auto ArkGameMode = Cast<AArkGameMode>(GetWorld()->GetAuthGameMode()))
		{
			ArkGameMode->GameEnded();
		}
	}
}

void AArkPlayingBoard::BeginPlay()
{
	Super::BeginPlay();

	SpawnBlockActors();
	ClearPreviewComponents();
}

TSubclassOf<AArkBonusParent> AArkPlayingBoard::GetBonusClass()
{
	if (BonusTypeByChance.Num() == 0 || !BonusTypeByChance[0].BonusClass)
	{
		return nullptr;
	}

	int32 TotalWeight = 0;

	for (const auto& CurrentBonus : BonusTypeByChance)
	{
		TotalWeight += CurrentBonus.DropChance * 100;
	}
	
	int32 RandomWeight = FMath::RandHelper(TotalWeight);
	
	for (const auto& CurrentBonus : BonusTypeByChance)
	{
		if (RandomWeight > CurrentBonus.DropChance * 100)
		{
			RandomWeight -= CurrentBonus.DropChance * 100;
		}
		else
		{
			return CurrentBonus.BonusClass;
		}
	}

	return nullptr;
}

void AArkPlayingBoard::BonusDestroyCubes(const int32 Amount)
{
	if (Amount <= 0) return;

	const int32 NumToDestroy = FMath::Min(Amount, BlockActors.Num());

	for (int32 i = 0; i < NumToDestroy; i++)
	{
		const int32 RandomIndex = FMath::RandHelper(BlockActors.Num());

		if (BlockActors.IsValidIndex(RandomIndex))
		{
			BlockActors[RandomIndex]->Destroy();
		}
	}
}
