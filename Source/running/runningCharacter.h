// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "runningCharacter.generated.h"

UCLASS(config=Game)
class ArunningCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ArunningCharacter();
	
	UFUNCTION()
	virtual void BeginPlay() override;
	
	//移动跑道所需变量
	UPROPERTY(VisibleAnywhere, Category = "Lane")
		int32 CurrentLane;
	UPROPERTY(VisibleAnywhere,Category = "Lane")
		int32 NewLane;
	UPROPERTY(EditAnyWhere,Category = "Lane")
		int32 LaneMin;
	UPROPERTY(EditAnyWhere, Category = "Lane")
		int32 LaneMax;
	UPROPERTY(EditAnyWhere, Category = "Lane")
		TArray<int32> LaneY;
	//玩家属性
	UPROPERTY(EditAnywhere,Category="Base")
		float RunningSpeed = 2.0f;
	UPROPERTY(EditAnywhere,Category="Base")
		FString UserName;
	UFUNCTION()
	void AddCoinCount();
	

	virtual void Tick(float DeltaTime) override;
	//死亡功能所需
public:
	UFUNCTION(BlueprintCallable)
	void Death();

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Death")
	UParticleSystem* DeathParticleSystem;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Death")
	USoundBase*  DeathSound;

	UPROPERTY()
	bool bIsDead = false;

protected:
	UFUNCTION()
	void OnDeath();

	UPROPERTY()
	FTimerHandle DeathHandle;
//
	
private:
	//移动跑道按键
	void MoveRight();
	void MoveLeft();
	 //
	void Save();
	void Load();
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override
	{
		// Set up gameplay key bindings
		check(PlayerInputComponent);
		PlayerInputComponent->BindAction("Save",IE_Pressed,this,&ArunningCharacter::Save);
		PlayerInputComponent->BindAction("Load",IE_Pressed,this,&ArunningCharacter::Load);
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
		PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ArunningCharacter::MoveRight);
		PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ArunningCharacter::MoveLeft);

	}
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};


