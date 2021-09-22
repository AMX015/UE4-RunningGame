// Copyright Epic Games, Inc. All Rights Reserved.

#include "runningCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "MySaveGame.h"
#include "runningGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// ArunningCharacter

ArunningCharacter::ArunningCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
}
/////////
///// Called when the game starts or when spawned
void ArunningCharacter::BeginPlay()
{
	Super::BeginPlay();

	ArunningGameMode* RunGameMode = Cast<ArunningGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RunGameMode);
}

void ArunningCharacter::AddCoinCount()
{
	ArunningGameMode* RunGameMode = Cast<ArunningGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	RunGameMode->AddCoinCount();
}



//////////////////////////////////////////////////////////////////////////
// Input
//Ticl调用
void ArunningCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, RunningSpeed);
}
//切换跑道
void ArunningCharacter::MoveRight()
{
	NewLane = CurrentLane + 1;
	if (NewLane > LaneMax)
	{
		NewLane = LaneMax;
	}
	FVector NewLocation = GetActorLocation();
	NewLocation.Y = LaneY[NewLane];
	SetActorLocation(NewLocation);
	CurrentLane = NewLane;
}

void ArunningCharacter::MoveLeft()
{
	NewLane = CurrentLane - 1;
	if (NewLane < LaneMin)
	{
		NewLane = LaneMin;
	}
	FVector NewLocation = GetActorLocation();
	NewLocation.Y = LaneY[NewLane];
	SetActorLocation(NewLocation);
	CurrentLane = NewLane;
}
//保存方法
void ArunningCharacter::Save()
{
	//创建SaveGame类实例
	UMySaveGame* SaveGameInstance =Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	//设置玩家保存属性=实例属性
	SaveGameInstance->UserName = this->UserName;
	//保存实例
	UGameplayStatics::SaveGameToSlot(SaveGameInstance,TEXT("SaveSlot"),0);

	
	GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Green,TEXT("Game Saved"));
	GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Green,this->UserName);
}
//载入方法
void ArunningCharacter::Load()
{
	//创建SaveGame类实例
	UMySaveGame* SaveGameInstance =Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	//将保存信息传递给实例
	SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot",0));
	//从实例中设置当前玩家属性
	this->UserName = SaveGameInstance ->UserName;
	
	GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Red,TEXT("Game Loaded"));
	GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Red,this->UserName);
}
//死亡方法
void ArunningCharacter::Death()
{

	const FVector Location =GetActorLocation();

	UWorld* World= GetWorld();
	if(!bIsDead)
	{
		if(World)
		{
			bIsDead = true;

			DisableInput(nullptr);
		
			if(DeathParticleSystem)
			{
				UGameplayStatics::SpawnEmitterAtLocation(World,DeathParticleSystem,Location);
			}

			if(DeathSound)
			{
				UGameplayStatics::PlaySoundAtLocation(World,DeathSound,Location);
			}

			GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Red,TEXT("角色死亡"));

			GetMesh()->SetVisibility(false);

			World->GetTimerManager().SetTimer(DeathHandle,this,&ArunningCharacter::OnDeath,1.0f,false);
		}
	}
}
void ArunningCharacter::OnDeath()
{
	bIsDead = false;
	
	if(DeathHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DeathHandle);
	}
	
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("RestartLevel"));
}



