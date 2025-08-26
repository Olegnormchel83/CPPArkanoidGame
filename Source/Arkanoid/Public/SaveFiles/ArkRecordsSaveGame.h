// Olegnormchel. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ArkRecordsSaveGame.generated.h"

UCLASS()
class ARKANOID_API UArkRecordsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<FString, int32> SavedRecords;
	
};
