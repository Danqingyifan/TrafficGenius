// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Person.generated.h"

UCLASS()
class GAMEJAM_API APerson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APerson();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OterComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	UFUNCTION()
	void Disappear();

public:
	UPROPERTY(BlueprintReadWrite)
	FVector ForwardVector;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float RunSpeed;

	FTimerHandle DestroyTimerHandle;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bIfBeCrashed = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAudioComponent> AudioComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USoundBase* HitSoundToPlay;
};
