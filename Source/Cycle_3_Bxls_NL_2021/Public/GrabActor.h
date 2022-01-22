// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

//includes added---------------------------
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
//----------------------------------------

#include "GrabActor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYCLE_3_BXLS_NL_2021_API UGrabActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabActor();

protected:
	// Called when the game starts
	FVector setupStartPoint()const;
	FVector setupEndPoint()const;
	

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category="grab")
	void GrabPressed(UPhysicsHandleComponent* ptrPhysicsHandle);
	
	UFUNCTION(BlueprintCallable, Category="grab")
	void GrabReleased(UPhysicsHandleComponent* ptrPhysicsHandle);

	UFUNCTION(BlueprintCallable)
	void UdpateHandlePos(UPhysicsHandleComponent* ptrPhysicsHandle);
	void Handle(UPhysicsHandleComponent* ptrPhysicsHandle, FHitResult Hit);

	UPROPERTY(EditDefaultsOnly) float flt_distanceGrab;
};
