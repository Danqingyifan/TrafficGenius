// Fill out your copyright notice in the Description page of Project Settings.


#include "GJ_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



void AGJ_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// 显示鼠标指针
	bShowMouseCursor = true;

	// 设置鼠标指针的类型（可选）
	DefaultMouseCursor = EMouseCursor::Crosshairs; // 设置默认鼠标指针类型
}

void AGJ_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGJ_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerMappingContext, 0);
	}
}
