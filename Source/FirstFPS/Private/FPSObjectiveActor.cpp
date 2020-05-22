// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectiveActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../FirstFPSCharacter.h"
#include "Engine/Engine.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCom"));
	MeshCom->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshCom->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	RootComponent = MeshCom;

	SphereCom = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCom"));
	SphereCom->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCom->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCom->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	
	SphereCom->SetupAttachment(MeshCom);
	
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	PlayParitcle();
}

// Called every frame
void AFPSObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSObjectiveActor::PlayParitcle()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle,GetActorLocation());
}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayParitcle();
	if (OtherActor)
	{
		Player = Cast<AFirstFPSCharacter>(OtherActor);
		Player->IsCarryingObject = true;
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Red,FString::Printf(TEXT("Pick.... ")));
		Destroy();
	}
}

