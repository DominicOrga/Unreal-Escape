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
	SetupPhysicsHandleComponent();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	DrawLineTraceDebugLine();

	// Update the grabbed component location based on the end of the line trace.
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetGrabReachLineEnd());
	}
}

/** Grab the object in reach. */
void UGrabber::Grab() 
{ 
	FHitResult Hit;

	GetFirstPhysicsBodyInReach(OUT Hit);

	AActor* HitActor = Hit.GetActor();

	// If an object is hit, then grab it.
	if (HitActor)
	{
		UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();
		PhysicsHandle->GrabComponent(ComponentToGrab, EName::NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), false);
	}
}

/** Release the grabbed object. */
void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

/** Find a physics handle component from the same owner, if one exists. */
void UGrabber::SetupPhysicsHandleComponent() 
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Component Handle Cannot be Found."));
	}
}

/**
 * Find an input component from the same owner and appropriately bind actions unto it.
 * Note: Input component is generated at run time.
 */
void UGrabber::SetupInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();

	if (Input)
	{
		Input->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component Cannot be Found."));
	}
}

/**
 * Run a line trace (Ray Cast) to find out the first physics object in reach.
 * @param Hit - A reference variable passed with a new hit object (if any).
 */
void UGrabber::GetFirstPhysicsBodyInReach(FHitResult& Hit)
{
	// Line Trace (A.K.A. Ray Cast) to detect collision
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetGrabReachLineStart(),
		GetGrabReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	AActor* HitActor = Hit.GetActor();

	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *HitActor->GetName());
	}
}

// Draw a line trace debug line to show grab range.
void UGrabber::DrawLineTraceDebugLine()
{
	DrawDebugLine(
		GetWorld(),
		GetGrabReachLineStart(),
		GetGrabReachLineEnd(),
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);
}

/**
 * @return the starting vector location of the grab reach line.
 */
FVector UGrabber::GetGrabReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}

/**
 * @return the end vector location of the grab reach line.
 */
FVector UGrabber::GetGrabReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

