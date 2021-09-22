// Copyright Epic Games, Inc. All Rights Reserved.

#include "runningGameMode.h"
#include "GameHud.h"
#include "runningCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ArunningGameMode::ArunningGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
void ArunningGameMode::BeginPlay()
{
	//UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor = true;

	UGameHud* GameHud = CreateWidget<UGameHud>(GetWorld(),GameHUDClass);
	if(GameHud != nullptr)
	{
		GameHud->InitializeHUD(this);
		GameHud->AddToViewport();
	}
	
	CreateInitialTile();
}
//初始化地面
void ArunningGameMode::CreateInitialTile()
{
	AMasterTile* Tile =AddFloorTile(false);
	for(int i =0;i<NumInitialTile;i++)
	{
		AddFloorTile(true);
	}
}
//生成地面方法
AMasterTile* ArunningGameMode::AddFloorTile(bool bSpawnItems)
{
	UWorld* World=GetWorld();
	if(World)
	{
		AMasterTile* Tile = World->SpawnActor<AMasterTile>(FloorTileClass,NextSpawnPoint);
		if(Tile)
		{
			if(bSpawnItems)
			{
				Tile->SpawnItems();
			}
			NextSpawnPoint = Tile->GetAttachTransform();
		}
	}

	return nullptr;
}

void ArunningGameMode::AddCoinCount()
{
	CoinCount += 1;

	OnCountChange.Broadcast(CoinCount);
}
