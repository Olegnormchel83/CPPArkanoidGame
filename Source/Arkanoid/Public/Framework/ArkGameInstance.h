// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArkGameInstance.generated.h"

UCLASS()
class ARKANOID_API UArkGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

	TMap<FString, int32> LevelRecords;

	FString SaveSlotName = "ArkRecordsSave";

	void SetGameSettings() const;

	void SaveRecords() const;

	void LoadRecords();

	void DeleteRecords() const;

public:
	UFUNCTION(BlueprintCallable, Category = "SaveRecords")
	void SetLevelRecord(const FString& LevelName, const int32 NewRecord);

	UFUNCTION(BlueprintPure, Category = "SaveRecords")
	int32 GetLevelRecord(const FString& LevelName) const;
	
};
