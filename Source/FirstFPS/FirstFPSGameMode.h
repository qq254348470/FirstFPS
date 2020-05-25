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
	void GameEnd(APawn* Pawn, bool Success);

	UFUNCTION(BlueprintImplementableEvent, Category = GM_Successed)
		void GM_Successed(APawn* Pawn,bool Success);

	UPROPERTY(EditDefaultsOnly, Category = CameraActor)
		TSubclassOf<AActor> CameraActor;
};



