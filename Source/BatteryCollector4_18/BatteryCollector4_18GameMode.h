// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryCollector4_18GameMode.generated.h"


// enum to store the curret state of gameplay
UENUM(BlueprintType)
enum class EBatteryPlayState :uint8
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};


UCLASS(minimalapi)
class ABatteryCollector4_18GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollector4_18GameMode();

	virtual void Tick(float DeltaTime) override;

	/**Returns power needed to win - needed for the HUD*/
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

	virtual void BeginPlay() override;
	
	/**Returns the current playing state */
	UFUNCTION(BlueprintPure,Category = "Power")
	EBatteryPlayState GetCurrentState() const;
	/**Sets a new playing state*/
	void SetCurrentState(EBatteryPlayState NewState);


protected:
	/**The rate at which the character loses power*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate;
	/**The power needed to win the GameMode*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float PowerToWin;

	/** The Widget class to use for our HUD screen*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;
	
	/**The instance of HUD*/
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	/**keeps track of the current playing state*/
	EBatteryPlayState CurrentState;
	TArray<class ASpawnVolume*> SpawnVolumeActors;

	/**Handle any function call that rely upon changing the playing state of our game*/
	void HandleNewState(EBatteryPlayState NewState);

};



