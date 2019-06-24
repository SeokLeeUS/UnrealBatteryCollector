// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector4_18GameMode.h"
#include "BatteryCollector4_18Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"

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


void ABatteryCollector4_18GameMode::BeginPlay()
{
	Super::BeginPlay();
	

	// find all spawn volume actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}
	
	SetCurrentState(EBatteryPlayState::EPlaying);

	// set the score to beat
	ABatteryCollector4_18Character* MyCharacter = Cast<ABatteryCollector4_18Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = (MyCharacter->GetInitialPower())*1.25f;

	}

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}



}


void ABatteryCollector4_18GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Check that we are using the battery collector character
	ABatteryCollector4_18Character* MyCharacter = Cast<ABatteryCollector4_18Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		// if the character's power is positive
		//if (MyCharacter->GetCurrentPower() > PowerToWin)
		//{
			// decrease the character's power using the decay rate
			//MyCharacter->UpdatePower(-DeltaTime * DecayRate*(MyCharacter->GetInitialPower()));
			//SetCurrentState(EBatteryPlayState::EWon);
		//}
		
	
		// If our power is greater than needed to win, set the game's state to Won
		if (MyCharacter->GetCurrentPower() > PowerToWin)
		{
			//SetCurrentState(EBatteryPlayState::EWon); dummy testing not sure why GetCurrentPower is greater than PowerToWin
			SetCurrentState(EBatteryPlayState::EWon);
			//MyCharacter->UpdatePower(-DeltaTime * DecayRate*(MyCharacter->GetInitialPower()));//testing
		}
		// if the character's power is positive
		else if (MyCharacter->GetCurrentPower() > 0)
		{
			// decrease the character's power using the delay rate
			MyCharacter->UpdatePower(-DeltaTime * DecayRate*(MyCharacter->GetInitialPower()));
		}
		else
		{
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}

}

float ABatteryCollector4_18GameMode::GetPowerToWin() const
{
	return PowerToWin;
}

EBatteryPlayState ABatteryCollector4_18GameMode::GetCurrentState() const
{
	return CurrentState;
}

void ABatteryCollector4_18GameMode::SetCurrentState(EBatteryPlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

void ABatteryCollector4_18GameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
		// if the game is playing
		case (EBatteryPlayState::EPlaying):
		{
			//spawn volumes active
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawningActive(true);
			}

		}
		break;
		// if we've won the game
		case (EBatteryPlayState::EWon):
		{
			//spawn volumes inactive
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawningActive(false);
				//Volume->SetSpawningActive(true);//experiment
			}
		}
		break;
		// if we've lost the game
		case (EBatteryPlayState::EGameOver):
		{
			//spawn volumes inactives
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawningActive(false);
			}
			//block player input
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
			{
				PlayerController->SetCinematicMode(true, false, false, true, true);
			}
			//ragdoll the character
			ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			if (MyCharacter)
			{
				MyCharacter->GetMesh()->SetSimulatePhysics(true);
				MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
			}
		}
		break;
		//unknown / default state
		default:
		case (EBatteryPlayState::EUnknown):
		{
			// do nothing
		}
		break;
		}
}