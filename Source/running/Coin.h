// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class RUNNING_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Comp")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Comp")
	UStaticMeshComponent* CoinMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Comp")
	USphereComponent* CoinSphere;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Sound")
	USoundBase* CoinSound;
	
	// Sets default values for this actor's properties
	ACoin();

protected:
	
	UFUNCTION(BlueprintCallable)
	virtual void CoinStartOverlay(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,
			UPrimitiveComponent* OtherComp,int32 OtherCOmIndex,bool bFromSweep,const FHitResult & SweepResult);

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
