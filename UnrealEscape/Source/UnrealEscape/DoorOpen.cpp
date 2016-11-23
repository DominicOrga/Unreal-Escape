#include "UnrealEscape.h"
#include "DoorOpen.h"

#define OUT

// Sets default values for this component's properties
UDoorOpen::UDoorOpen() 
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorOpen::BeginPlay() 
{
	Super::BeginPlay();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no Trigger Volume attached to Door Open Component."), *GetOwner()->GetName());
	}
}


// Called every frame
void UDoorOpen::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) 
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!PressurePlate)
	{
		return;
	}

	// Opens the door when the authorized actor collides with the pressure plate
	if (GetTotalMassOfActorsOnPlate() > 20.f) 
	{ 
		OpenDoor(); 
	}

	// Checks if the door is open and closes it after a specified amount of time
	if (bIsDoorOpen) 
	{
		float CurrentTime = GetWorld()->GetTimeSeconds();
		float ElapsedTime = CurrentTime - LastTimeDoorOpened;

		if (ElapsedTime >= DoorCloseDelay) 
		{
			CloseDoor();
		}
	}

}

void UDoorOpen::OpenDoor() 
{
	GetOwner()->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
	LastTimeDoorOpened = GetWorld()->GetTimeSeconds();
	bIsDoorOpen = true;
}

void UDoorOpen::CloseDoor() 
{
	GetOwner()->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	bIsDoorOpen = false;
}

float UDoorOpen::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	if (!PressurePlate) 
	{ 
		return TotalMass; 
	}

	// Find all the overlapping actors. 
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them and sum up their masses.
	for (const AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->GetRootPrimitiveComponent()->GetMass();
	}

	return TotalMass;
}