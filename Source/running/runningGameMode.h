// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MasterTile.h"
#include "GameFramework/GameModeBase.h"
#include "runningGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinCountChange,int32,CoinCount);

UCLASS(minimalapi)
class ArunningGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ArunningGameMode();
	
	UPROPERTY(EditAnywhere,Category="Config")
	TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY(VisibleInstanceOnly,Category="RunTime")
	class UGameHud* GameHUD;

	UPROPERTY(EditAnywhere,Category="Config")
	TSubclassOf<AMasterTile> FloorTileClass;
	
	UPROPERTY(EditAnywhere,Category="Config")
	int32 NumInitialTile = 10;

	UPROPERTY(VisibleAnywhere)
	FTransform NextSpawnPoint;

	UPROPERTY(VisibleAnywhere)
	FVector SpawnPointLocation;

	UPROPERTY(VisibleAnywhere)
	int32 CoinCount;

	UFUNCTION(BlueprintCallable)
	void CreateInitialTile();

	UFUNCTION(BlueprintCallable)
	AMasterTile* AddFloorTile(const bool bSpawnItems);

	UPROPERTY(BlueprintAssignable,BlueprintCallable,Category="Event")
	FOnCoinCountChange OnCountChange;
	
	UFUNCTION(BlueprintCallable)
	void AddCoinCount();

protected:
	virtual void BeginPlay() override;
};



