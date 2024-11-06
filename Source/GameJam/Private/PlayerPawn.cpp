// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Barrier.h"
#include "Car.h"
#include "EnhancedInputComponent.h"
#include "GJ_PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	CollectBarrier();
}

void APlayerPawn::CollectBarrier()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABarrier::StaticClass(), FoundActors);
	for(int i = 0;i<4;i++)
	{
		for (AActor* Actor : FoundActors)
		{
			ABarrier* tempBarrier = Cast<ABarrier>(Actor); 
			if(i == 0)
			{
				if(tempBarrier->CarDirection == ECarDirection::Down)
				{
					Barriers.Add(tempBarrier);
				}
			}
			else if(i == 1)
			{
				if(tempBarrier->CarDirection == ECarDirection::Up)
				{
					Barriers.Add(tempBarrier);
				}
				
			}else if(i == 2)
			{
				if(tempBarrier->CarDirection == ECarDirection::Right)
				{
					Barriers.Add(tempBarrier);
				}
			}
			else if(i == 3)
			{
				if(tempBarrier->CarDirection == ECarDirection::Left)
				{
					Barriers.Add(tempBarrier);
				}
			}
		}
	}

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (AGJ_PlayerController* GJ_PlayerController = Cast<AGJ_PlayerController>(Controller))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			//No Jump Action For Graves

			EnhancedInputComponent->BindAction(GJ_PlayerController->ControllLightWAction, ETriggerEvent::Started, this, &APlayerPawn::ControlLightW);
			EnhancedInputComponent->BindAction(GJ_PlayerController->ControllLightSAction, ETriggerEvent::Started, this, &APlayerPawn::ControlLightS);
			EnhancedInputComponent->BindAction(GJ_PlayerController->ControllLightAAction, ETriggerEvent::Started, this, &APlayerPawn::ControlLightA);
			EnhancedInputComponent->BindAction(GJ_PlayerController->ControllLightDAction, ETriggerEvent::Started, this, &APlayerPawn::ControlLightD);

			EnhancedInputComponent->BindAction(GJ_PlayerController->ClickAction, ETriggerEvent::Started, this, &APlayerPawn::Click);
		}
	}
}
void APlayerPawn::ControlLightW(const FInputActionValue& Value)
{
	Barriers[0]->Activate();
}
void APlayerPawn::ControlLightS(const FInputActionValue& Value)
{
	Barriers[1]->Activate();
}
void APlayerPawn::ControlLightA(const FInputActionValue& Value)
{
	Barriers[2]->Activate();
}
void APlayerPawn::ControlLightD(const FInputActionValue& Value)
{
	Barriers[3]->Activate();
}

void APlayerPawn::Click(const FInputActionValue& Value)
{
	// 获取玩家控制器
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	FHitResult HitResult;
	bool bHit = PlayerController->GetHitResultUnderCursor(ECC_PhysicsBody, false, HitResult);
	
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		ACar* HitCar = Cast<ACar>(HitActor);
		if (HitCar)
		{
			// 生成一个随机角度（例如，范围是 -30 到 30 度）
			float Angle = FMath::FRandRange(-RandomAngle, RandomAngle);
	
			// 创建旋转
			FRotator RandomRotator(0.0f, Angle, 0.0f); // Yaw方向上的旋转

			// 将 ForwardVector 旋转
			FVector ImpulseDirection = RandomRotator.RotateVector(HitCar->ForwardVector);
			
			UPrimitiveComponent* HitComponent = HitResult.GetComponent();
			FVector Impulse = ImpulseDirection * 3000;
			Impulse.Z = 5000;
            
			if (HitComponent->IsSimulatingPhysics())
			{
				HitComponent->AddImpulse(Impulse, NAME_None, true);
			}

			DamagedCarAmount += 1;
			
			// 设置五秒后自动销毁
			if (!HitCar->bIsDamaged)
			{
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [HitCar]()
				{
					HitCar->Destroy(); // 销毁车辆
				}, 4.0f, false);
			}
		}
	}
}


