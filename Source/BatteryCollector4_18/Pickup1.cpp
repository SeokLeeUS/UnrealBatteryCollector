// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup1.h"
#include "Components/StaticMeshComponent.h" 


// Sets default values
APickup1::APickup1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
	// All pickups start active
	bIsActive = true;
}

// Called when the game starts or when spawned
void APickup1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickup1::IsActive()
{
	return bIsActive;
}

void APickup1::SetActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}

void APickup1::WasCollected_Implementation()
{
	//Log a debug message
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *PickupDebugString);
}