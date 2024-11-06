// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"

#include "Car.h"
#include "PlayerPawn.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APerson::APerson()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent); 
}

// Called when the game starts or when spawned
void APerson::BeginPlay()
{
	Super::BeginPlay();
	// 绑定碰撞事件
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APerson::OnBeginOverlap);
}

// Called every frame
void APerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(ForwardVector * RunSpeed * DeltaTime);
}

// Called to bind functionality to input
void APerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APerson::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OterComp, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult)
{
	ACar* Car = Cast<ACar>(OtherActor);
	if (Car)
	{
		AController* PlayerController = GetWorld()->GetFirstPlayerController();
		APawn* ControlledPawn = PlayerController->GetPawn();

		if (ControlledPawn)
		{
			APlayerPawn* PlayerPawn = Cast<APlayerPawn>(ControlledPawn);
			if (PlayerPawn)
			{
				if (!bIfBeCrashed)
				{
					bIfBeCrashed = true;
					
					if (AudioComponent && HitSoundToPlay)
					{
						AudioComponent->SetSound(HitSoundToPlay);  // 设置音效
						AudioComponent->Play(); // 播放音效
					}
					PlayerPawn->DeadPersonAmount += 1;
				}
			}
		}
		RunSpeed = 0;

		FVector Impluse = FVector(0, 0, 0); // 向上的额外力量
		Impluse = Car->ForwardVector * Car->CurrentSpeed * 2;
		Impluse.Z = Car->CurrentSpeed * 1.5;
		if (OverlappedComponent->IsSimulatingPhysics())
		{
			OverlappedComponent->AddImpulse(Impluse, NAME_None, true);
			// 添加旋转（假设您想要一个随机的旋转角度）
			FRotator RandomRotation = FRotator(FMath::RandRange(-30.0f, 30.0f), FMath::RandRange(-30.0f, 30.0f), FMath::RandRange(-30.f, 30.f));
        
			// 将旋转转换为四元数
			FQuat RotationQuat = FQuat(RandomRotation);
        
			// 施加旋转
			GetCapsuleComponent()->AddTorqueInRadians(RotationQuat.Vector() * 1000); // 根据需要调整旋转的大小
		}

		if (GetMesh()->GetAnimInstance())
		{
			GetMesh()->GetAnimInstance()->StopAllMontages(0.2f); // 停止所有动画
		}
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Ragdoll"));
		GetCapsuleComponent()->SetMassScale(NAME_None,0.1f);
		GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &APerson::Disappear, 3.0f, false);
	}
}

void APerson::Disappear()
{
	Destroy();
}
