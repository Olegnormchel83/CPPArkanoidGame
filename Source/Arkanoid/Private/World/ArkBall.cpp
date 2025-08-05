// Olegnormchel. All rights reserved


#include "World/ArkBall.h"

// Sets default values
AArkBall::AArkBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArkBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArkBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

