// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrier.h"

#include "Components/AudioComponent.h"

// Sets default values
ABarrier::ABarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StaticMeshComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent); 
	
}

// Called when the game starts or when spawned
void ABarrier::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ABarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABarrier::Activate()
{
	bIsActive = !bIsActive;
	if(bIsActive) // 红灯
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Z -= 1000;
		SetActorLocation(NewLocation);

		if (AudioComponent && RedLightSoundToPlay)
		{
			AudioComponent->SetSound(RedLightSoundToPlay);  // 设置音效
			AudioComponent->Play(); // 播放音效
		}
	}
	else // 绿灯
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Z += 1000;
		SetActorLocation(NewLocation);

		if (AudioComponent && GreenLightSoundToPlay)
		{
			AudioComponent->SetSound(GreenLightSoundToPlay);  // 设置音效
			AudioComponent->Play(); // 播放音效
		}
	}
}
