// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHud.h"

void UGameHud::InitializeHUD(ArunningGameMode* RunGameMode)
{
	CoinCount->SetText(FText::AsNumber(0));

	RunGameMode->OnCountChange.AddDynamic(this,&UGameHud::SetCurrentCoinCount);
}
void UGameHud::SetCurrentCoinCount(const int32 CurrentCoinCount)
{
	CoinCount->SetText(FText::AsNumber(CurrentCoinCount));
}

