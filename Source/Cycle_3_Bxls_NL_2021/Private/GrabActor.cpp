// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabActor.h"

// Sets default values for this component's properties
UGrabActor::UGrabActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	flt_distanceGrab=500.f; //by default equals 500.0
	

	// ...
}


FVector UGrabActor::setupStartPoint()const
{

	return this->GetOwner()->GetActorLocation();
}

FVector UGrabActor::setupEndPoint()const
{
	FVector actorForward = GetOwner()->GetActorForwardVector();
	return (actorForward * flt_distanceGrab)+setupStartPoint();
}

void UGrabActor::GrabPressed(UPhysicsHandleComponent* ptrPhysicsHandle)
{
	FHitResult Hit;
	FCollisionQueryParams params;
	FCollisionObjectQueryParams objectsParam;
	objectsParam.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
	
	//debug direction et collision ligne
	DrawDebugLine(GetWorld(), setupStartPoint(), setupEndPoint(), FColor::Green, false, 5.0f, 0, 2.0f);

	//creation raycast, si le raycast touche bien un objet alors on affiche grabCollision
	if (this->GetOwner()->GetWorld()->LineTraceSingleByObjectType(Hit, setupStartPoint(), setupEndPoint(), objectsParam, params)) {
		UE_LOG(LogTemp, Warning, TEXT("grabCollision"));
		//grabed object :
		Handle(ptrPhysicsHandle, Hit);
			
	}
}

void UGrabActor::Handle(UPhysicsHandleComponent* ptrPhysicsHandle, FHitResult Hit){

	if(Hit.GetActor())
	{
		ptrPhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(),"none", Hit.GetComponent()->GetOwner()->GetActorLocation());
	}
}




void UGrabActor::GrabReleased(UPhysicsHandleComponent* ptrPhysicsHandle)
{
	//quand on release la touche alors l'objet grabed est relaché
	if (ptrPhysicsHandle != nullptr) {
		ptrPhysicsHandle->ReleaseComponent();
		UE_LOG(LogTemp, Warning, TEXT("grabReleased"));
	}

	
}

void UGrabActor::UdpateHandlePos(UPhysicsHandleComponent* ptrPhysicsHandle)
{
	if (ptrPhysicsHandle->GrabbedComponent) {
		ptrPhysicsHandle->SetTargetLocation(setupEndPoint());
	}

}





