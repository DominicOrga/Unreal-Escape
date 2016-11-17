// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealEscape.h"
#include "DoorOpen.h"


// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	AuthorizedActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UDoorOpen::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if(PressurePlate->IsOverlappingActor(AuthorizedActor)) 
	{
		OpenDoor();
	}
	// ...
}

// Opens the door
void UDoorOpen::OpenDoor() {

	// Get Owner
	AActor* Owner = GetOwner();

	// Make Rotator
	FRotator NewRotation = FRotator(0.f, OpenAngle, 0.f);

	// Set new rotator to owner
	Owner->SetActorRotation(NewRotation);
}

