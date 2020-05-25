// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Engine.h"
#include "../FirstFPSCharacter.h"
#include "../FirstFPSGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200));
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandOverLap);
	RootComponent = OverlapComp;
	OverlapComp->SetHiddenInGame(false);
	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	DecalComp->DecalSize = FVector(200);
	DecalComp->SetupAttachment(OverlapComp);
	
}


void AFPSExtractionZone::HandOverLap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, UKismetSystemLibrary::GetObjectName(OtherActor));
	UE_LOG(LogTemp, Error, TEXT("OtherActor : %s"), *UKismetSystemLibrary::GetObjectName(OtherActor));
	AFirstFPSCharacter *Player = Cast<AFirstFPSCharacter>(OtherActor);
	if (Player)
	{
		if (Player->IsCarryingObject)
		{
			AFirstFPSGameMode *GM = Cast<AFirstFPSGameMode>(GetWorld()->GetAuthGameMode());
			if (GM)
			{
				GM->GameEnd(Player,true);
			}
		}
		else
		{
			UGameplayStatics::PlaySound2D(GetWorld(), TipSound);
		}
	}
	
}


