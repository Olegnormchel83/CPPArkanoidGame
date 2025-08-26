// Olegnormchel. All rights reserved

#include "ArkGameInstance.h"

#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "SaveFiles/ArkRecordsSaveGame.h"

void UArkGameInstance::Init()
{
	Super::Init();

	SetGameSettings();
	LoadRecords();
}

void UArkGameInstance::SetGameSettings() const
{
	if (!GEngine || !GetWorld()) return;
	
	GEngine->GameUserSettings->SetVSyncEnabled(true);
	GEngine->GameUserSettings->ApplySettings(true);
	GEngine->GameUserSettings->SaveSettings();

	GEngine->Exec(GetWorld(), TEXT("t.maxFPS 60"));
}

void UArkGameInstance::SaveRecords() const
{
	auto SaveGameFile = Cast<UArkRecordsSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (!SaveGameFile)
		SaveGameFile = Cast<UArkRecordsSaveGame>(UGameplayStatics::CreateSaveGameObject(UArkRecordsSaveGame::StaticClass()));

	if (!SaveGameFile) return;

	SaveGameFile->SavedRecords = LevelRecords;
	UGameplayStatics::SaveGameToSlot(SaveGameFile, SaveSlotName, 0);
}

void UArkGameInstance::LoadRecords()
{
	const auto LoadedSaveGame = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	const auto SaveGameFile = Cast<UArkRecordsSaveGame>(LoadedSaveGame);

	if (!SaveGameFile) return;

	LevelRecords = SaveGameFile->SavedRecords;
}

void UArkGameInstance::DeleteRecords() const
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		UGameplayStatics::DeleteGameInSlot(SaveSlotName, 0);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, ("Deleted Records: %s", *SaveSlotName));
	}
}

void UArkGameInstance::SetLevelRecord(const FString& LevelName, const int32 NewRecord)
{
	if (NewRecord > GetLevelRecord(LevelName))
	{
		LevelRecords.Add(LevelName, NewRecord);
		SaveRecords();
	}
}

int32 UArkGameInstance::GetLevelRecord(const FString& LevelName) const
{
	return LevelRecords.FindRef(LevelName);
}
