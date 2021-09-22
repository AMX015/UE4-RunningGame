// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"


/**
 * 
 */
UCLASS()
class RUNNING_API  UMySaveGame:
public USaveGame
{
	GENERATED_BODY()

	public:

	UMySaveGame();

	UPROPERTY(EditAnywhere, Category = "Save")
	FString UserName;

	UPROPERTY(EditAnywhere, Category = "Save")
	FString SaveSlotName;

	UPROPERTY(EditAnywhere, Category = "Save")
	int32 UserIndex;

	UPROPERTY(EditAnywhere,Category = "Save")
	int32 UserScore;
	
};
