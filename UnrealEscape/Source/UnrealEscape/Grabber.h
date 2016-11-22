#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* Input = nullptr;

public:	
	// Sets default values for this component's properties
	UGrabber();
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	/** Grab the object in reach. */
	void Grab();

	/** Release the grabbed object. */
	void Release();

	/** Find a physics handle component from the same owner, if one exists. */
	void SetupPhysicsHandleComponent();
	
	/** 
	 * Find an input component from the same owner and appropriately bind actions unto it.
	 * Note: Input component is generated at run time.
	 */
	void SetupInputComponent();

	/**
	 * Run a line trace (Ray Cast) to find out the first physics object in reach.
	 * @param Hit - A reference variable passed with a new hit object (if any).
	 */
	void GetFirstPhysicsBodyInReach(FHitResult& Hit);

	// Draw a line trace debug line to show its range.
	void DrawLineTraceDebugLine();

	/**
	 * @return the starting vector location of the grab reach line.
	 */
	FVector GetGrabReachLineStart();

	/**
	 * @return the end vector location of the grab reach line.
	 */
	FVector GetGrabReachLineEnd();
};
