// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnCar.h"
#include "GameFramework/Pawn.h"
#include "Car.generated.h"


UCLASS()
class GAMEJAM_API ACar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();

	UPROPERTY(EditAnywhere)
	float MaxSpeed;

	UPROPERTY(EditAnywhere)
	float AcceleratedSpeed;

	UPROPERTY(EditAnywhere)
	float DeceleratedSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECarDirection Direction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CountCarNumber() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Raycast();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Accelerate();
	void Brake();

	UFUNCTION()
	void Disappear();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void HandleOnDestroyed(AActor* DestroyedActor);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UBoxComponent> BoxComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UArrowComponent> ArrowComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class USceneComponent> RaycastPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ForwardVector = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RaycastDistance = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIfAccelerate = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDamaged = false;

	float CurrentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ImpluseScale = 1.0f;
};
