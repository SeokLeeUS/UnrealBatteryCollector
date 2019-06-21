// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryCollector4_18GameMode.generated.h"

UCLASS(minimalapi)
class ABatteryCollector4_18GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollector4_18GameMode();

	virtual void Tick(float DeltaTime) override;

protected:
	/**The rate at which the character loses power*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Power")
	float DecayRate;

};



