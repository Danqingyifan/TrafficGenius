// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPerson.h"

#include "Car.h"
#include "Person.h"
#include "Components/ArrowComponent.h"

// Sets default values
ASpawnPerson::ASpawnPerson()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	SpawnLocationScene = CreateDefaultSubobject<USceneComponent>("SpawnLocationScene");
	SpawnLocationScene->SetupAttachment(StaticMesh);
	SpawnActorDirection = CreateDefaultSubobject<UArrowComponent>("SpawnActorDirection");
	SpawnActorDirection->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void ASpawnPerson::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawnPerson::DelayedStart, 1.0f, false);
}

// Called every frame
void ASpawnPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnPerson::SpawnPerson()
{
	FVector SpawnLocation = SpawnLocationScene->GetComponentLocation();
	FRotator SpawnRotation = SpawnActorDirection->GetForwardVector().Rotation();

	int type = FMath::RandRange(0, 3);
	TSubclassOf<class APerson> PersonType = PersonTypes[0];
	APerson* SpawnedPerson = GetWorld()->SpawnActor<APerson>(PersonType, SpawnLocation, SpawnRotation);

	if (SpawnedPerson)
	{
		SpawnedPerson->ForwardVector = SpawnActorDirection->GetForwardVector();
	}

	float respawnTime = FMath::FRandRange(MinSpawnTime, MaxSpawnTime);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawnPerson::SpawnPerson, respawnTime, false);
}

void ASpawnPerson::DelayedStart()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawnPerson::SpawnPerson, 0.1f, false);
}
