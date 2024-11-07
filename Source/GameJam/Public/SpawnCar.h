// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnCar.generated.h"

UENUM(BlueprintType)
enum class ECarDirection : uint8
{
	Up UMETA(DisplayName = "Up"),  
	Down UMETA(DisplayName = "Down"),
	Left UMETA(DisplayName = "Left"),        
	Right UMETA(DisplayName = "Right"),      
};

UCLASS()
class GAMEJAM_API ASpawnCar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnCar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnCar();
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TSubclassOf<class ACar>> CarTypes;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ECarDirection CarDirection;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UArrowComponent> SpawnActorDirection;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class USceneComponent> SpawnLocationScene;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TObjectPtr<class ACar>> ContainingCars;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MinSpawnTime;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxSpawnTime;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float Car1MaxSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Car2MaxSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Car3MaxSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Car4MaxSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Car1MassScale;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Car2MassScale;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Car3MassScale;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Car4MassScale;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CarImpluseScale = 1.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float FixedCarRotationZ = 0.0f;
public:
	// 声明静态变量
	static int32 CarNumbers;

	// 用于获取静态变量的函数
	UFUNCTION(BlueprintCallable)
	static int32 GetCarNumbers();
	
	UFUNCTION()
	void DelayedStart();
};
