// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHoleActor.generated.h"

UCLASS(Blueprintable)
class FIRSTFPS_API ABlackHoleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHoleActor();

	UFUNCTION()
		void OverlapinnerSphere(UPrimitiveComponent* OverlappedCom, AActor* OtherActor,UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	


public:
	UPROPERTY(EditDefaultsOnly, Category = Components)
		class UStaticMeshComponent *StaticMeshCom;
	UPROPERTY(VisibleAnywhere, Category = Components)
		class USphereComponent *InnerSphereCom;
	UPROPERTY(VisibleAnywhere, Category = Components)
		class USphereComponent *OuterSphereCom;
	UPROPERTY(EditDefaultsOnly, Category = FX)
		class UParticleSystem* Boom;

};
