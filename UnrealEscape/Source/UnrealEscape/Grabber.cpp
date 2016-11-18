// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber initialized."));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// Gets a copy of the player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation);

	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), 
		*PlayerViewPointLocation.ToString(), 
		*PlayerViewPointRotation.ToString()
	);

	// Represents the end of the grab reachability
	FVector LineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// Draws a debug line to visualize grab reachability
	DrawDebugLine(
		GetWorld(), 
		PlayerViewPointLocation, 
		LineEnd, 
		FColor(255, 0, 0), 
		false, 
		0.f, 
		0.f, 
		10.f
	);

	// The colliding object
	FHitResult Hit;

	// Line Trace (A.K.A. Ray Cast) to detect collision
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	// Logs the object returned by the line trace
	AActor* HitActor = Hit.GetActor();
	if (HitActor != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *(HitActor->GetName()));
	}
}
