// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnCar.h"
#include "GameFramework/Actor.h"
#include "Barrier.generated.h"


UCLASS()
class GAMEJAM_API ABarrier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Activate();

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ECarDirection CarDirection;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsActive = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USoundBase* RedLightSoundToPlay;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USoundBase* GreenLightSoundToPlay;
};
