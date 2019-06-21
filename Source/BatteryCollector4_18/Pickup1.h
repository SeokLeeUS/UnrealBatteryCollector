// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup1.generated.h"

UCLASS()
class BATTERYCOLLECTOR4_18_API APickup1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bIsActive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }

	/** Return Whether or not the pick up is active**/
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	/**Allows other classes to safely change whether or not pickup is active**/
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool NewPickupState);

	/**Function to call when the pickup is collected*/
	
    
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	virtual void WasCollected_Implementation();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;

	
	
};
