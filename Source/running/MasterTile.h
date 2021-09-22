// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coin.h"
#include "Coin.h"
#include "Obstacles.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "MasterTile.generated.h"

UCLASS()
class RUNNING_API AMasterTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterTile();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class ArunningGameMode* RunGameMode;

	UPROPERTY()
	FTimerHandle DestroyHandle;

public:	

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent*StaticMeshComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UArrowComponent*SpawnPoint;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UArrowComponent* Lane0;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UArrowComponent* Lane1;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UArrowComponent* Lane2;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Collision")
	class UBoxComponent* CollisionMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Obstacle")
	TSubclassOf<AObstacles> SmallObstaclesClass;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Obstacle")
	TSubclassOf<AObstacles> BigObstaclesClass;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Coin")
	TSubclassOf<ACoin> BaseCoinClass;
	
	const FTransform& GetAttachTransform() const
	{
		return SpawnPoint->GetComponentTransform();
	}
		

	UFUNCTION()
		virtual  void FloorBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,
			UPrimitiveComponent* OtherComp,int32 OtherCOmIndex,bool bFromSweep,const FHitResult & SweepResult);

	UFUNCTION()
	void DestroyFloor();

	UFUNCTION(BlueprintCallable)
	void SpawnItems();

	UFUNCTION()
	void SpawnItemsInLane(UArrowComponent* Lane);
	
	
};
