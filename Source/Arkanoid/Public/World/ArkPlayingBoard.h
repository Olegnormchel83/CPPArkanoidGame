// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArkPlayingBoard.generated.h"

class AArkBlock;

USTRUCT(BlueprintType)
struct FBonusTypeChance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> BonusClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
	float DropChance = 0.2f;
	
};

UCLASS()
class ARKANOID_API AArkPlayingBoard : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot = nullptr;

	UPROPERTY()
	TArray<UStaticMeshComponent*> PreviewComponents;

	UPROPERTY()
	TArray<AArkBlock*> BlockActors;

	void CreatePreviewComponents();

	void ClearPreviewComponents();

	void SpawnBlockActors();

	UFUNCTION()
	void OnBlockDestroyed(AActor* DestroyedBlock);
	
public:	
	AArkPlayingBoard();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void BeginPlay() override;

	TSubclassOf<AActor> GetBonusClass();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base",
		meta = (ToolTip = "Блюпринт кубика"))
	TSubclassOf<AArkBlock> BlockClassForSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base",
		meta = (ToolTip = "Меш для первью"))
	UStaticMesh* PreviewMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base")
	FVector BlockScale = FVector(0.5f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base")
	int32 GridSizeX = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base")
	int32 GridSizeY = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base")
	int32 SpacingX = 60;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base")
	int32 SpacingY = 60;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Game",
		meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1", UIMax = "1"))
	float GameDifficulty = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Game",
		meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1", UIMax = "1"))
	float BonusChance = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Base")
	TArray<FBonusTypeChance> BonusTypeByChance;
};
