// OBJECTIF DE LA CLASSE :
//- Ouvrir ou fermer la porte en fct d'une masse limite 
//- Masse étant calculée par la masse en kg de chaque objet posé en face de la porte
//-> effet balance : si la somme des masses des objets posées devant la porte est supérieure à la masse limite alors la porte s'ouvre
//-> à contrario si la porte est ouverte et que la balance indique un résultat inférieur ou égale à la masse limite alors la porte se referme



//----------------------------------------------------------------------------------------------//
//POUR CELA UTILISATION NECESSAIRES DES ELEMENTS SUIVANTS :

//-timeline + curve float  pour -> animation ouverture/fermeture porte
//-Une triggerZone gérée par la classe TriggerVolume_Door pour -> détecter les objets 
//-Deux delegates custom event pour -> communiquer entre la classe DoorBalance et TriggerVolume_Door
//-Comparaison de masse entre les objets et une limite fixée 


#pragma once

#include "CoreMinimal.h"
#include "TriggerVolume_Door.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "DoorBalance.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYCLE_3_BXLS_NL_2021_API UDoorBalance : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDoorBalance();

protected:
	virtual void BeginPlay() override;
	

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Delegate trigger
	UFUNCTION(BlueprintCallable)
	void GetTriggerCollision(UTriggerVolume_Door* triggerVolume);
	UFUNCTION(BlueprintCallable)
	void SetupDelegateTriggerCollision();

	//comparison obj name instance
	FString GetNameFromObjectCollided(AActor* actor);
	UFUNCTION(BlueprintCallable)
	void CompareObjectToObjectReference(AActor* actor);

	//animation door
	UFUNCTION(BlueprintCallable)
	void SetupTimeline();
	UFUNCTION()
	void ToogleAndPlayDoor();
	UFUNCTION()
	void UpdateAnimationDoor();

	


private :

	//variables delegate
	UTriggerVolume_Door* triggerVolumeInstance;

	//variables et timeline pour faire l'animation de la porte
	UPROPERTY(EditAnywhere) UCurveFloat* doorCurve;	
	UPROPERTY() FTimeline timeline;
	float curveFloatValue;
	float timelineValue;
	float sensDoorRotation;
	bool isAnimDoorFinished;
	bool isDoorOpen;
	FRotator doorRotation;
	

	//propriétés de comparaison entre les acteurs entrant et sortant la trigger zone
	UPROPERTY()
	FString str_InstObj;
	UPROPERTY(EditDefaultsOnly) FString str_RefObj;
	
};
