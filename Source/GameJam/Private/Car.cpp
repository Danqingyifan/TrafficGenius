// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"

#include "Barrier.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ACar::ACar()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	SetRootComponent(BoxComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(BoxComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(BoxComponent);

	RaycastPosition = CreateDefaultSubobject<USceneComponent>("RaycastPosition");
	RaycastPosition->SetupAttachment(BoxComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent->SetupAttachment(BoxComponent);
	
	BoxComponent->OnComponentHit.AddDynamic(this, &ACar::OnHit);
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	OnDestroyed.AddDynamic(this, &ACar::HandleOnDestroyed);

	bIfAccelerate = true;
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsDamaged)
	{
		Brake();
		return;
	}

	Raycast();

	if (bIfAccelerate == true)
	{
		Accelerate();
	}
	else
	{
		Brake();
	}

	if(FMath::Abs(GetActorRotation().Yaw - FixedCarRotationZ) > 1.0f)
	{
		FRotator NewRotation = FRotator(0, FixedCarRotationZ, 0);
        SetActorRotation(NewRotation);
	}
	AddActorWorldOffset(ForwardVector * CurrentSpeed * DeltaTime);
}

void ACar::Raycast()
{
	FHitResult HitResult;
	float Distance = RaycastDistance;
	FVector Start = RaycastPosition->GetComponentLocation(); // 起点
	FVector End = Start + (ForwardVector * Distance); // 终点

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // 忽略自身

	// 执行射线检测
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();

		// Case 1: Hit Car
		ACar* HitCar = Cast<ACar>(HitActor);
		if (HitCar && HitCar->Direction == Direction)
		{
			bIfAccelerate = false;
		}

		// Case 2: Hit CheckingWall
		ABarrier* HitBarrier = Cast<ABarrier>(HitActor);
		if (HitBarrier && HitBarrier->CarDirection == Direction)
		{
			bIfAccelerate = false;
		}
	}
	else
	{
		bIfAccelerate = true;
	}
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACar::Accelerate()
{
	CurrentSpeed += AcceleratedSpeed * GetWorld()->DeltaTimeSeconds;
	if (CurrentSpeed > MaxSpeed)
		CurrentSpeed = MaxSpeed;
}

void ACar::Brake()
{
	CurrentSpeed -= DeceleratedSpeed * GetWorld()->DeltaTimeSeconds;
	if (CurrentSpeed < 0)
		CurrentSpeed = 0;
}

void ACar::Disappear()
{
	Destroy();
}


void ACar::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 检查是否撞到另一辆车
	if (OtherActor && OtherActor != this) // 确保不是撞到自己
	{
		ACar* OtherCar = Cast<ACar>(OtherActor);
		if (OtherCar)
		{
			bIsDamaged = true;
			OtherCar->bIsDamaged = true;

			FVector Impluse = FVector(0, 0, 0); // 向上的额外力量
			Impluse = ForwardVector * CurrentSpeed * ImpluseScale;
			if (HitComponent->IsSimulatingPhysics())
			{
				HitComponent->AddImpulse(Impluse, NAME_None, true);
			}

			if (AudioComponent && HitSoundToPlay)
			{
				AudioComponent->SetSound(HitSoundToPlay);  // 设置音效
				AudioComponent->Play(); // 播放音效
			}
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				Destroy(); // 销毁车辆
			}, 4.0f, false);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [OtherCar]()
			{
				if (OtherCar)
				{
					OtherCar->Destroy(); // 销毁车辆
				}
			}, 4.0f, false);
		}
	}
}

void ACar::HandleOnDestroyed(AActor* DestroyedActor)
{
	ASpawnCar::CarNumbers--;
}
