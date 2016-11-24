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
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) 
	{ 
		OnDoorOpen.Broadcast();
	}
	else
	{
		OnDoorClose.Broadcast();
	}
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