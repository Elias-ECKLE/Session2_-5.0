// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TriggerVolume_Door2.h"
#include "Components/TimelineComponent.h"
#include "DoorBalance2.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYCLE_3_BXLS_NL_2021_API UDoorBalance2 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorBalance2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//Delegate trigger
	UFUNCTION(BlueprintCallable)
	void GetTriggersCollision(UTriggerVolume_Door2* triggerZone1, UTriggerVolume_Door2* triggerZone2, UTriggerVolume_Door2* triggerZone3);
	UFUNCTION(BlueprintCallable)
	void SetupDelegateTriggerCollision();
	//delegate
	TArray<UTriggerVolume_Door2*> array_TriggersZone;
	TArray<bool> array_IsTriggersZoneCompleted;

	//compare triggers zone state
	UFUNCTION()
	void UpdateTriggersZoneState(int32 tagTrigger);
	UFUNCTION(BlueprintCallable)
	void CompareTriggersState();

	
	//variables et timeline pour faire l'animation de la porte
	UPROPERTY(EditAnywhere) UCurveFloat* doorCurve;	
	UPROPERTY() FTimeline timeline;
	float curveFloatValue;
	float timelineValue;
	float sensDoorRotation;
	bool isAnimDoorFinished;
	bool isDoorOpen;
	FRotator doorRotation;
	//animation door
	UFUNCTION(BlueprintCallable)
	void SetupTimeline();
	UFUNCTION()
	void ToogleAndPlayDoor();
	UFUNCTION()
	void UpdateAnimationDoor();
		
};
