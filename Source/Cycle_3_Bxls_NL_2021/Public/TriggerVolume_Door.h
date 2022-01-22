// OBJECTIF DE CLASSE:
//-Créer une triggerZone qui détecte les objets entrant et sortant
//-En fct de ces changements, celle-ci appelle des scripts dans DoorBalance

//-------------------------------------------------------------------------------------------//


//POUR CELA UTILISATION NECESSAIRE DE :
//-Une triggerZone géree par boxCollider
//-Deux events : beginOverlap et EndOverlap pour détecter quand il y a des objets entrant et sortant de la triggerZone
//-Deux delegate custom events déclenchant des scripts dans DoorBalance

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "TriggerVolume_Door.generated.h"

//on commencer par créer un type qui va servir pour la création de deux custom events dynnamiques soit 
//lorqu'un objet entre dans la triggerZone -> FDelegateTriggerBegin
//l'autre lorsqu'il en sort -> FDelegateTriggerEnd
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateTriggerBegin,AActor*, otherActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateTriggerEnd,AActor*, otherActor);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYCLE_3_BXLS_NL_2021_API UTriggerVolume_Door : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerVolume_Door();
	//UDoorBalance doorBalance;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//Trigger Zone
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
	void SetupBoxCollider();
	
	//variables custom event
	UPROPERTY(BlueprintAssignable)
	FDelegateTriggerBegin triggerVolumeBeginCollision; //type de variable crée plus haut avec la macro delegate
	UPROPERTY(BlueprintAssignable)
	FDelegateTriggerEnd triggerVolumeEndCollision; //type de variable crée plus haut avec la macro delegate


private :

	UBoxComponent* boxCollider;
	
};