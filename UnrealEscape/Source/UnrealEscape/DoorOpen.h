// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorOpen.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float OpenAngle = -90.f;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	float LastTimeDoorOpened;

	bool bIsDoorOpen = false;

public:	
	// Sets default values for this component's properties
	UDoorOpen();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void OpenDoor();

	void CloseDoor();

	float GetTotalMassOfActorsOnPlate();
};
