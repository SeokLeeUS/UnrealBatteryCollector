// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector4_18GameMode.h"
#include "BatteryCollector4_18Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ABatteryCollector4_18GameMode::ABatteryCollector4_18GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// base decay rate
	DecayRate = 0.01f;

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

}

void ABatteryCollector4_18GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Check that we are using the battery collector character
	ABatteryCollector4_18Character* MyCharacter = Cast<ABatteryCollector4_18Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		// if the character's power is positive
		if (MyCharacter->GetCurrentPower() > 0)
		{
			// decrease the character's power using the delay rate
			MyCharacter->UpdatePower(-DeltaTime * DecayRate*(MyCharacter->GetInitialPower()));
		}
		
	}

}
