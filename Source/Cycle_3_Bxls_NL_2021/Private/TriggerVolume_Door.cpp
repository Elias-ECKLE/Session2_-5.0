// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_Door.h"

// ------------------------------------------Defaults methods----------------------------------------------
UTriggerVolume_Door::UTriggerVolume_Door()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerVolume_Door::BeginPlay()
{
	Super::BeginPlay();
	//on cherche le composant BoxCollision et on le paramètre en fonction de deux events OnOnverlapBegin & OnOverlapEnd
	//SetupBoxCollider();
}

void UTriggerVolume_Door::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


//---------------------------------------------TriggerZone------------------------------------------------
/****************************************************************************************************
Description : Methode qui récupère le component BoxCollider puis qui le lie aux deux événements OverlapBegin et OverlapEnd
La BoxCollider est la triggerZone en lien avec DoorBalance
Input : 
Output : None
Note ://
******************************************************************************************************/
void UTriggerVolume_Door::SetupBoxCollider()
{
	boxCollider = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (ensure(boxCollider))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Box collider Component find"));
		//comme OnOverlapBegin et OnEndOverlap agissent comme des custom event dynamiques, il faut leur ajouter un AddDynamic
		boxCollider->OnComponentBeginOverlap.AddDynamic(this,&UTriggerVolume_Door::OnOverlapBegin);
		boxCollider->OnComponentEndOverlap.AddDynamic(this,&UTriggerVolume_Door::OnOverlapEnd);
	}
}

/****************************************************************************************************
Description : Quand un objet entre dans la triggerZone alors le script ci-dessous s'enclenche
Input : reçoit en paramètres tous les possibles éléments auquel la triggerZone peut entrer en collision avec 
Output : None
Note ://
******************************************************************************************************/
void UTriggerVolume_Door::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("OverlapBegin_TriggerVolumeOk"));
	//lorqu'un objet entre dans la triggerZone alors on déclenche le script associé avec le delegate dans DoorBalance -> AddBalanceMass(actor)
	//on lui passe en paramètre l'acteur en collision 
	triggerVolumeBeginCollision.Broadcast(OtherActor);
}

/****************************************************************************************************
Description : Quand un objet sort dela triggerZone alors le script ci-dessous s'enclenche
Input : reçoit en paramètres tous les possibles éléments auquel la triggerZone peut entrer en collision avec 
Output : None
Note ://
******************************************************************************************************/
void UTriggerVolume_Door::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("OverlapEnd_TriggerVolumeOk"));
	//lorqu'un objet entre dans la triggerZone alors on déclenche le script associé avec le delegate dans DoorBalance -> SoustrBalanceMass(actor)
	//on lui passe en paramètre l'acteur en collision 
	triggerVolumeEndCollision.Broadcast(OtherActor);
}



