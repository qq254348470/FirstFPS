// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "../FirstFPSGameMode.h"
#include "UObject/ObjectMacros.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"





// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeePawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this,&AFPSAIGuard::OnNoiseHeard);

}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	StartRotator = GetActorRotation();
	StartState = EAIState::Idle;
	CurrentPoint = FirstPoint;
	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(),CurrentPoint);
}

void AFPSAIGuard::OnSeePawn(APawn *Pawn)
{
	if(Pawn) 
	{
		UE_LOG(LogTemp,Error,TEXT("OnSeePawn :%s"),*UKismetSystemLibrary::GetObjectName(Pawn));
		DrawDebugSphere(GetWorld(),Pawn->GetActorLocation(),32,12,FColor::Red,false,10,0,3);	
		AFirstFPSGameMode *GM = Cast<AFirstFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{									
			GM->GameEnd(Pawn, false);
		}
		SetState(EAIState::Find);
		AController *AIController = GetController();
		if (AIController) 
		{
			AIController->StopMovement();		
		}

	}
}


void AFPSAIGuard::OnNoiseHeard(APawn *Pawn ,const FVector& Location ,float Volume)
{
	if (StartState == EAIState::Find)
		return;
	DrawDebugSphere(GetWorld(),Location,32,12,FColor::Green,false,10,0,3);
	FRotator NewRotator;	
	NewRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);
	
	SetActorRotation(FRotator(0,NewRotator.Yaw,0));
	UE_LOG(LogTemp, Error, TEXT("Rotator : %s - %s"),*(NewRotator.ToString()),*(this->GetName()));
	GetWorldTimerManager().ClearTimer(TimerHandleRotator);
	GetWorldTimerManager().SetTimer(TimerHandleRotator, this, &AFPSAIGuard::ResetRotation, 3.0f);

	SetState(EAIState::Hear);

	AController *AIController = GetController();
		if (AIController) 
		{
			AIController->StopMovement();		
		}

}



void AFPSAIGuard::ResetRotation()
{
	SetActorRotation(StartRotator);
	UE_LOG(LogTemp, Error, TEXT("Reset Rotation.."));
	SetState(EAIState::Idle);
	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(),CurrentPoint);
}



void AFPSAIGuard::SetState(EAIState NewState)
{
	if (StartState == NewState)
		return;
	StartState = NewState;
	OnStateChange(NewState);
	UE_LOG(LogTemp,Error,TEXT("Current State ..."));
}



// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentPoint)
	{
		FVector ABLength = GetActorLocation() - CurrentPoint->GetActorLocation();
		ABLength.Z = 0;
		float Distance = ABLength.Size();
		FString Name = UKismetSystemLibrary::GetObjectName(CurrentPoint);
		UE_LOG(LogTemp, Error, TEXT("距离 %s:%f"),*Name,Distance);
		if ( Distance<150 )
		{
			MoveNextPoint();
			
		}
	}
	
	
}

void AFPSAIGuard::MoveNextPoint()
{
	if (CurrentPoint ==nullptr||CurrentPoint ==SecondPoint)
	{
		CurrentPoint = FirstPoint;
	}
	else
	{
		CurrentPoint = SecondPoint;
	}
	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(),CurrentPoint);
}



