// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstFPSGameMode.h"
#include "FirstFPSHUD.h"
#include "FirstFPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AFirstFPSGameMode::AFirstFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFirstFPSHUD::StaticClass();
}

void AFirstFPSGameMode::GameEnd(APawn* Pawn)
{
	if (Pawn)
	{
		Pawn->DisableInput(nullptr);
		UE_LOG(LogTemp, Error, TEXT("GM : %s"), *UKismetSystemLibrary::GetObjectName(Pawn));
		GM_Successed(Pawn);
		if (CameraActor)
		{
			AActor* NewCamer;
			TArray<AActor *> ReturnCamera;
			UGameplayStatics::GetAllActorsOfClass(this,CameraActor,ReturnCamera);
			if (ReturnCamera.Num()>0)
			{
				NewCamer = ReturnCamera[0];
				APlayerController *PC = Cast<APlayerController>(Pawn->GetController());
				if (PC)
				{
					PC->SetViewTargetWithBlend(NewCamer,0.5F,EViewTargetBlendFunction::VTBlend_Linear,0.0f,false);
				}
			}

		}
	}
	
}

