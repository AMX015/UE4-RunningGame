// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

#include "runningCharacter.h"
#include "runningGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACoin::ACoin()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>("CoinMesh");
	CoinMesh->SetupAttachment(SceneComponent);

	CoinSphere = CreateDefaultSubobject<USphereComponent>("CoinSphere");
	CoinSphere->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	CoinSphere->OnComponentBeginOverlap.AddDynamic(this,&ACoin::CoinStartOverlay);
}

void ACoin::CoinStartOverlay(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp
	, int32 OtherCOmIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	ArunningCharacter* RunChara = Cast<ArunningCharacter>(OtherActor);
	if(RunChara)
	{
		const FVector Location =GetActorLocation();
		UWorld* World = GetWorld();
		UGameplayStatics::PlaySoundAtLocation(World,CoinSound,Location);

		RunChara->AddCoinCount();
		this->Destroy();
	}
}




