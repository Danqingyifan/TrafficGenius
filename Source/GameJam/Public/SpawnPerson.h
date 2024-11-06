// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "GameFramework/Actor.h"
#include "SpawnPerson.generated.h"

UCLASS()
class GAMEJAM_API ASpawnPerson : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPerson();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnPerson();

	UFUNCTION()
	void DelayedStart();

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UArrowComponent> SpawnActorDirection;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class USceneComponent> SpawnLocationScene;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TSubclassOf<APerson>> PersonTypes;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MinSpawnTime;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxSpawnTime;
};
