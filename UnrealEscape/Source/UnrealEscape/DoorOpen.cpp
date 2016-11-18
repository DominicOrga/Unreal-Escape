// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealEscape.h"
#include "DoorOpen.h"


// Sets default values for this component's properties
UDoorOpen::UDoorOpen() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorOpen::BeginPlay() {
	Super::BeginPlay();

	AuthorizedActor = GetWorld()->GetFirstPlayerController()->GetPawn();

}


// Called every frame
void UDoorOpen::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) {
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (PressurePlate != NULL) {
		// Opens the door when the authorized actor collides with the pressure plate
		if (PressurePlate->IsOverlappingActor(AuthorizedActor)) { OpenDoor(); }

		// Checks if the door is open and closes it after a specified amount of time
		if (bIsDoorOpen) {
			float CurrentTime = GetWorld()->GetTimeSeconds();
			
			if (CurrentTime - LastTimeDoorOpened >= DoorCloseDelay) {
				CloseDoor();
			}
		}
	}
}

// Opens the door
void UDoorOpen::OpenDoor() {
	GetOwner()->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
	LastTimeDoorOpened = GetWorld()->GetTimeSeconds();
	bIsDoorOpen = true;
}

// Closes the door
void UDoorOpen::CloseDoor() {
	GetOwner()->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	bIsDoorOpen = false;
}

