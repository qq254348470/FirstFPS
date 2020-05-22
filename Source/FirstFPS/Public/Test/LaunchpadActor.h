// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchpadActor.generated.h"

UCLASS()
class FIRSTFPS_API ALaunchpadActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchpadActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly , Category = "Components")
		class UBoxComponent *OverlapComp;
	UPROPERTY(EditDefaultsOnly, Category = "LaunchParameter")
		float LaunchAngle;
	UPROPERTY(EditDefaultsOnly , Category = "LaunchParameter")
		float LaunchForce;
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
