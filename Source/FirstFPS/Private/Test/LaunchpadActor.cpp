// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Test/LaunchpadActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "../FirstFPSCharacter.h"

// Sets default values
ALaunchpadActor::ALaunchpadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200));
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this,&ALaunchpadActor::OnOverlap);
	OverlapComp->SetHiddenInGame(false);
	RootComponent = OverlapComp;
	
	
}

// Called when the game starts or when spawned
void ALaunchpadActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaunchpadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALaunchpadActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	FRotator LaunchRotator = GetActorRotation();
	LaunchRotator.Yaw += LaunchAngle;
	FVector LaunchDirection = LaunchRotator.Vector()*LaunchForce;
	AFirstFPSCharacter *Player = Cast<AFirstFPSCharacter>(OtherActor);
	if (Player)
	{	FVector Force = (OtherActor->GetActorLocation() - GetActorLocation())*LaunchForce;
		Player->LaunchCharacter(Force, true, true);
		UE_LOG(LogTemp, Error, TEXT("Player: %s"), *UKismetSystemLibrary::GetObjectName(Player));
	}
	else if (OtherComp&&OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddForce(LaunchDirection,NAME_None,true);
		UE_LOG(LogTemp, Error, TEXT("OtherCom: %s"), *UKismetSystemLibrary::GetObjectName(OtherComp));
	}
}

