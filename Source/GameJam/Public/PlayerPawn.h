// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class ABarrier;
class ACar;
class ATrafficLight;
struct FInputActionValue;

UCLASS()
class GAMEJAM_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CollectBarrier();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ControlLightS(const FInputActionValue& Value);
	void ControlLightW(const FInputActionValue& Value);
	void ControlLightA(const FInputActionValue& Value);
	void ControlLightD(const FInputActionValue& Value);
	void Click(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ABarrier*> Barriers;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float RandomAngle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int DamagedCarAmount = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int DeadPersonAmount = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USoundBase* ClickCarSoundToPlay;
};
