// Olegnormchel. All rights reserved

#include "ArkPaddle.h"

AArkPaddle::AArkPaddle()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AArkPaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArkPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

