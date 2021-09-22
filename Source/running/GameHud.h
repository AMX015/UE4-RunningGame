// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "runningGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameHud.generated.h"

/**
 * 
 */
UCLASS()
class RUNNING_API UGameHud : public UUserWidget
{
	GENERATED_BODY()

	public:
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	class UTextBlock* CoinCount;

	UFUNCTION(BlueprintCallable)
	void InitializeHUD(ArunningGameMode* RunGameMode);

	UFUNCTION(BlueprintCallable)
	void SetCurrentCoinCount(int32 CurrentCoinCount);
	
};
