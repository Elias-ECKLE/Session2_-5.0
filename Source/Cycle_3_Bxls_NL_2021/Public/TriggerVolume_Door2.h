// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "TriggerVolume_Door2.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateTriggerCompleted,int32, tag);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYCLE_3_BXLS_NL_2021_API UTriggerVolume_Door2 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerVolume_Door2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//gestion collisions
	//Trigger Zone
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
	void SetupBoxCollider();
	

	//comparaisons masse
	void AddMassTriggerZone(AActor* actor);
	void SoustrMassTriggerZone(AActor* actor);
	void UpdateMass(float flt_valueOperate, bool isIncrm);
	float GetMassFromObjectCollided(AActor* actor);
	void CompareBalanceToMassMax();

	//delegate
	//variables custom event
	UPROPERTY(BlueprintAssignable)
	FDelegateTriggerCompleted triggerCompletedTag; //type de variable crée plus haut avec la macro delegate
	UPROPERTY(EditAnywhere)
	int32 int_Tag;



private :

	//trigger zone
	UBoxComponent* boxCollider;
	
	//comparison mass
	float flt_massActuelle;
	UPROPERTY()
	float flt_massMax;
	UPROPERTY()
	bool isTriggerZoneCompleted;
		
};
