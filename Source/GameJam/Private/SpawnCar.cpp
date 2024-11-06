// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnCar.h"

#include "Car.h"
#include "EngineUtils.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

int32 ASpawnCar::CarNumbers = 0;

// Sets default values
ASpawnCar::ASpawnCar()
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
void ASpawnCar::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawnCar::DelayedStart, 1.0f, false);
	CarNumbers = 0;
}

// Called every frame
void ASpawnCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnCar::SpawnCar()
{
	FVector SpawnLocation = SpawnLocationScene->GetComponentLocation();
	FRotator SpawnRotation = SpawnActorDirection->GetForwardVector().Rotation();

	int type = FMath::RandRange(0, 3);
	TSubclassOf<class ACar> CarType = CarTypes[type];
	
	ACar* SpawnedCar = GetWorld()->SpawnActor<ACar>(CarType, SpawnLocation, SpawnRotation);

	if (SpawnedCar)
	{
		if(type == 0)
		{
			SpawnedCar->MaxSpeed = Car1MaxSpeed;
			SpawnedCar->BoxComponent->SetMassScale(NAME_None,Car1MassScale);

		}
		else if(type == 1)
		{
			SpawnedCar->MaxSpeed = Car2MaxSpeed;
			SpawnedCar->BoxComponent->SetMassScale(NAME_None,Car2MassScale);

		}
		else if(type == 2)
		{
			SpawnedCar->MaxSpeed = Car3MaxSpeed;
			SpawnedCar->BoxComponent->SetMassScale(NAME_None,Car3MassScale);

		}
		else if(type == 3)
		{
			SpawnedCar->MaxSpeed = Car4MaxSpeed;
			SpawnedCar->BoxComponent->SetMassScale(NAME_None,Car4MassScale);

		}

		SpawnedCar->ForwardVector = SpawnActorDirection->GetForwardVector();
		SpawnedCar->Direction = CarDirection;
		SpawnedCar->ImpluseScale = CarImpluseScale;
		CarNumbers++;
		
		ContainingCars.Add(SpawnedCar);
	}
	
	float respawnTime = FMath::FRandRange(MinSpawnTime, MaxSpawnTime);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawnCar::SpawnCar, respawnTime, false);
}

int32 ASpawnCar::GetCarNumbers()
{
	return CarNumbers;
}

void ASpawnCar::DelayedStart()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawnCar::SpawnCar, 0.1f, false);
}