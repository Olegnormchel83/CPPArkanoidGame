// Olegnormchel. All rights reserved

#include "ArkBonusDestroyCubes.h"

#include "ArkPlayingBoard.h"
#include "EngineUtils.h"

AArkBonusDestroyCubes::AArkBonusDestroyCubes()
{
	Value = 3.f;
}

void AArkBonusDestroyCubes::BonusAction(AArkPaddle* Paddle)
{
	for (TActorIterator<AArkPlayingBoard> It(GetWorld()); It; ++It)
	{
		if (const auto CurrentBoard = *It)
		{
			CurrentBoard->BonusDestroyCubes(Value);
		}
	}
	
	Super::BonusAction(Paddle);
}
