// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/BlackHoleActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/LogMacros.h"


// Sets default values
ABlackHoleActor::ABlackHoleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshCom;
	InnerSphereCom = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphere"));
	InnerSphereCom->SetupAttachment(StaticMeshCom);
	InnerSphereCom->SetSphereRadius(100);
	//InnerSphereCom->OnComponentBeginOverlap.AddDynamic(this, &ABlackHoleActor::OverlapinnerSphere);

	OuterSphereCom = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphere"));
	OuterSphereCom->SetupAttachment(StaticMeshCom);
	OuterSphereCom->SetSphereRadius(3000);

}

// Called when the game starts or when spawned
void ABlackHoleActor::BeginPlay()
{
	Super::BeginPlay();
	InnerSphereCom->OnComponentBeginOverlap.AddDynamic(this, &ABlackHoleActor::OverlapinnerSphere);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),Boom,GetActorLocation(),FRotator(0,0,0),FVector(5,5,5));
	
}

// Called every frame
void ABlackHoleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> OverlappingComps;
	TArray<UPrimitiveComponent*> Comps;
	OuterSphereCom->GetOverlappingComponents(OverlappingComps);
	InnerSphereCom->GetOverlappingComponents(Comps);
	for (int32 a =0;a<OverlappingComps.Num();a++)
	{
		UPrimitiveComponent *CurrentComp = OverlappingComps[a];
		const float SphereRadius = OuterSphereCom->GetScaledSphereRadius();
		const float ForceStrength = -2000;
		FString Name = FString::FromInt(a)+" : "+UKismetSystemLibrary::GetObjectName(CurrentComp);
		CurrentComp->AddRadialForce(GetActorLocation(), SphereRadius,ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Name);
		
	}
	for (int32 a = 0; a < Comps.Num(); a++)
	{
		UPrimitiveComponent *CurrentComp = OverlappingComps[a];
		if (CurrentComp->GetOwner() != this)
		{
			FString Name = FString::FromInt(a) + " : " + UKismetSystemLibrary::GetObjectName(CurrentComp->GetOwner());
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
			//CurrentComp->GetOwner()->Destroy();
		}
	}
}

void ABlackHoleActor::OverlapinnerSphere(UPrimitiveComponent* OverlappedCom, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString Name = UKismetSystemLibrary::GetObjectName(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Name);

	UE_LOG(LogTemp,Warning,TEXT("name %s ..%d"),*Name,OtherBodyIndex);
	OtherActor->Destroy();

		
}



