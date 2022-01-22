// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorsPosition.h"



// Sets default values for this component's properties
UActorsPosition::UActorsPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorsPosition::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorsPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GEngine != nullptr) {
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, *getName());
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, *getPos().ToString());
	}

	//UE_LOG(LogTemp, Warning, TEXT("tests"));
	//UE_LOG(LogTemp, Warning, TEXT("Name : %s, Position : %s"), *getName(), *getPos().ToString());


	
}

const FString UActorsPosition::getName()
{
	
	return this->GetOwner()->GetName();
}

const FVector UActorsPosition::getPos()
{
	return this->GetOwner()->GetActorLocation();
}

