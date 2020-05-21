// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

UCLASS(Blueprintable)
class FIRSTFPS_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PlayParitcle();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	UPROPERTY(VisibleAnywhere,Category =Components)
	class UStaticMeshComponent *MeshCom;
	UPROPERTY(VisibleAnywhere,Category = Components)
	class USphereComponent *SphereCom;
	UPROPERTY(EditDefaultsOnly, Category = Particle)
	class UParticleSystem* Particle;

	class AFirstFPSCharacter* Player;

};
