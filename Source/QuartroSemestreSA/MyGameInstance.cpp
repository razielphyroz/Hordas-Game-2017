// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

void UMyGameInstance::IncreaseDeadEnemies()
{
	DeadEnemies++;
	UE_LOG(LogTemp, Warning, TEXT("%d dinimigos mortos."), DeadEnemies);
}


