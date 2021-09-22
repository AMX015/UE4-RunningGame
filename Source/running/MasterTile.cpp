// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterTile.h"

#include "runningCharacter.h"
#include "runningGameMode.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMasterTile::AMasterTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(SceneComponent);
//创建地面	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("FloorMesh");
	StaticMeshComp->SetupAttachment(SceneComponent);
	FRotator FloorRotatpr = StaticMeshComp->GetComponentRotation();
	FloorRotatpr.Yaw = 90.f;
	StaticMeshComp->SetWorldRotation(FloorRotatpr);

//创建碰撞盒
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionMesh->SetupAttachment(SceneComponent);
	CollisionMesh->SetBoxExtent(FVector(32.f,500.f,200.f));
	CollisionMesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
//创建箭头指示物
	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("Direction");
	SpawnPoint->SetupAttachment(SceneComponent);
//创建跑道指示
	Lane0 = CreateDefaultSubobject<UArrowComponent>("Lane 0");
	Lane0->SetupAttachment(SceneComponent);
	Lane1 = CreateDefaultSubobject<UArrowComponent>("Lane 1");
	Lane1->SetupAttachment(SceneComponent);
	Lane2 = CreateDefaultSubobject<UArrowComponent>("Lane 2");
	Lane2->SetupAttachment(SceneComponent);
}


// Called when the game starts or when spawned
void AMasterTile::BeginPlay()
{
	Super::BeginPlay();

	RunGameMode = Cast<ArunningGameMode,AGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RunGameMode);

	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this,&AMasterTile::FloorBeginOverlap);
}
//碰撞事件
void AMasterTile::FloorBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,
		UPrimitiveComponent* OtherComp,int32 OtherCOmIndex,bool bFromSweep,const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Red,TEXT("碰撞并生成新的地块"));

	//检查是否是玩家角色触发
	ArunningCharacter* RunCharacter = Cast<ArunningCharacter>(OtherActor);
	if(RunCharacter)
	{
		RunGameMode->AddFloorTile(true);

		GetWorldTimerManager().SetTimer(DestroyHandle,this,&AMasterTile::DestroyFloor,2.f,false);
		
	}
}
//自毁事件
void AMasterTile::DestroyFloor()
{
	if(DestroyHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}

	this->Destroy();
}
//生成各种道君障碍
void AMasterTile::SpawnItems()
{
	if(IsValid(SmallObstaclesClass) && IsValid(BigObstaclesClass))
	{
		SpawnItemsInLane(Lane0);
		SpawnItemsInLane(Lane1);
		SpawnItemsInLane(Lane2);
	}
}
//具体生成方法
void AMasterTile::SpawnItemsInLane(UArrowComponent* Lane)
{
	const float RandomVal = FMath::FRandRange(0.f,1.f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform& SpawnLocation = Lane->GetComponentTransform();
	
	if(UKismetMathLibrary::InRange_FloatFloat(RandomVal,0.8f,1.0f,true,true))
	{
		AObstacles* SmallObstacle = GetWorld()->SpawnActor<AObstacles>(SmallObstaclesClass,SpawnLocation,SpawnParameters);
	}
	else if(UKismetMathLibrary::InRange_FloatFloat(RandomVal,0.6f,0.79f,true,true))
	{
		AObstacles* SmallObstacle = GetWorld()->SpawnActor<AObstacles>(BigObstaclesClass,SpawnLocation,SpawnParameters);
	}
	else if(UKismetMathLibrary::InRange_FloatFloat(RandomVal,0.1f,0.59f,true,true))
	{
		ACoin* Coin = GetWorld()->SpawnActor<ACoin>(BaseCoinClass,SpawnLocation,SpawnParameters);
	}
}



