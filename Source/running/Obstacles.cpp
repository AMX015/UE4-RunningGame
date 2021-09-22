// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles.h"

#include "runningCharacter.h"

// Sets default values
AObstacles::AObstacles()
{
	ObstacleScene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = ObstacleScene;
	ObstaclesMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ObstaclesMesh->SetupAttachment(ObstacleScene);

	ObstaclesMesh->OnComponentHit.AddDynamic(this,&AObstacles::OnObstalceHit);
}
//碰撞事件
void AObstacles::OnObstalceHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	ArunningCharacter* RunChara = Cast<ArunningCharacter>(OtherActor);

	if(RunChara)
	{
		RunChara->Death();
	}
}



