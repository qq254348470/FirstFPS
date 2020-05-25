// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

UENUM(BlueprintType)
enum class EAIState:uint8
{
	None	UMETA(DisplayName = "空"),
	Idle 	UMETA(DisplayName = "闲置"),
	Find 	UMETA(DisplayName = "找到"),
	Hear	UMETA(DisplayName = "听到")
};

UCLASS(Blueprintable)
class FIRSTFPS_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = Components)
		class UPawnSensingComponent *PawnSensingComp;
	UFUNCTION()
		void OnSeePawn(APawn *Pawn);

	UFUNCTION()
		void OnNoiseHeard(APawn *Pawn, const FVector& Location, float Volume);

	UFUNCTION()
		void ResetRotation();

	FRotator StartRotator;
	FTimerHandle TimerHandleRotator;


	EAIState StartState;
	void SetState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AIState")
		void OnStateChange(EAIState NewState);

	UPROPERTY(EditAnywhere, Category = "AI")
		bool Patrol;
	UPROPERTY(EditAnywhere,Category = "AI")
		AActor *FirstPoint;
	UPROPERTY(EditAnywhere,Category = "AI")
	    AActor *SecondPoint;

	AActor *CurrentPoint;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveNextPoint();

	
};
