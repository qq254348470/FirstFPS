// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstFPSGameMode.generated.h"

UCLASS(minimalapi)
class AFirstFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFirstFPSGameMode();
	void GameEnd(APawn* Pawn);

	UFUNCTION(BlueprintImplementableEvent, Category = GM_Successed)
		void GM_Successed(APawn* Pawn);

	UPROPERTY(EditDefaultsOnly, Category = CameraActor)
		TSubclassOf<AActor> CameraActor;
};



