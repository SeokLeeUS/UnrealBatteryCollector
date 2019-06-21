// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup1.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR4_18_API ABatteryPickup : public APickup1
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABatteryPickup();

	/**override the WasCollected function - use Implementation because it's a Blueprint Native Event*/
	void WasCollected_Implementation() override;
	
	/**public way to access the battery's power level*/
	float GetPower();


	/**Function to call when the pickup is collected*/
	//UFUNCTION(BlueprintNativeEvent)
	//void WasCollected() override;
	//virtual void WasCollected_Implementation();


protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	/** set the amount of power the battery gives to the character*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (B1lueprintProtected = "true"))
	float BatteryPower;
	
};
