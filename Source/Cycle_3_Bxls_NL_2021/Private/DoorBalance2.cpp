// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorBalance2.h"

// Sets default values for this component's properties
UDoorBalance2::UDoorBalance2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	isDoorOpen=false;

	array_IsTriggersZoneCompleted.Add(false);
	array_IsTriggersZoneCompleted.Add(false);
	array_IsTriggersZoneCompleted.Add(false);
}


// Called when the game starts
void UDoorBalance2::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDoorBalance2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	timeline.TickTimeline(DeltaTime);
	CompareTriggersState();
}



//------------------------------------------------delegate-----------------------------------------------------
void UDoorBalance2::GetTriggersCollision(UTriggerVolume_Door2* triggerZone1, UTriggerVolume_Door2* triggerZone2,
	UTriggerVolume_Door2* triggerZone3)
{
	if(ensure(triggerZone1))
	{
		array_TriggersZone.Add(triggerZone1);
	}
	if(ensure(triggerZone2))
	{
		array_TriggersZone.Add(triggerZone2);
	}
	if(ensure(triggerZone3))
	{
		array_TriggersZone.Add(triggerZone3);
	}
	

}


void UDoorBalance2::SetupDelegateTriggerCollision()
{
		array_TriggersZone[0]->triggerCompletedTag.AddDynamic(this,&UDoorBalance2::UDoorBalance2::UpdateTriggersZoneState);
		array_TriggersZone[1]->triggerCompletedTag.AddDynamic(this,&UDoorBalance2::UDoorBalance2::UpdateTriggersZoneState);
		array_TriggersZone[2]->triggerCompletedTag.AddDynamic(this,&UDoorBalance2::UDoorBalance2::UpdateTriggersZoneState);	
}


//compare triggers zone states

void UDoorBalance2::UpdateTriggersZoneState(int32 tagTrigger)
{
		array_IsTriggersZoneCompleted[tagTrigger] = true;
		if (GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(9, 5, FColor::Blue,TEXT("TriggerZoneSuppCompleted"));
		}
	
}

void UDoorBalance2::CompareTriggersState()
{

		if(array_IsTriggersZoneCompleted[0]==true && array_IsTriggersZoneCompleted[1]==true && array_IsTriggersZoneCompleted[2]==true)
		{
			isDoorOpen=true;
			//UE_LOG(LogTemp,Warning,TEXT("doorOpen"));
			ToogleAndPlayDoor();
		}
		else
		{
			isDoorOpen=false;
		}
		
	
	
}


//---------------------------------------------animation door--------------------------------------------------
/****************************************************************************************************
Description : Methode qui configure la timeline gérant le mouvement de la porte en fonction d'une courbe de type float -> ouverte ou fermée
Input : 
Output : None
Note ://
******************************************************************************************************/
void UDoorBalance2::SetupTimeline()
{
	//si l'élément "float curve" existe alors on met en place le point d'entrée de la timeline
	if(doorCurve)
	{	
		//on crée une variable qui va suivre la progression de la timeline
		FOnTimelineFloat progressFunction;
		//on la lie ensuite à une méthode qu'on va appeler à chaque avancée de la timeline.
		//C'est dans cette timeline qu'on va maj la //rotation de la porte 
		progressFunction.BindUFunction(this,FName("UpdateAnimationDoor"));
		UE_LOG(LogTemp, Warning, TEXT("SetupTimelineOk"));

		//enfin on lie la courbe doorCurve à ProgressFunction
		timeline.AddInterpFloat(doorCurve,progressFunction);
		timeline.SetLooping(false);
	}
	else //si on ne trouve pas la courbe door curve alors on affiche un msg d'erreur
	{
		if (GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(5, 10, FColor::Red, TEXT("Curve float non initialisée"));
		}
		UE_LOG(LogTemp, Error, TEXT("Curve float non init, veuillez l'ajouter dans BP_OpenDoor -> DoorBalance"));
	}
}

/****************************************************************************************************
Description : Methode qui maj rotation porte en fonction de l'avancée de la timeline dans le temps et de son avancée sur la courbe door curve
Input : 
Output : None
Note ://
******************************************************************************************************/
void UDoorBalance2::UpdateAnimationDoor()
{
	//en fonction de l'endroit où on se trouve dans la timeline, on récupère la valeur en float de l'élément curveDoor associé
	timelineValue = timeline.GetPlaybackPosition();
	curveFloatValue = doorCurve->GetFloatValue(timelineValue);
	//enfin avec ces données, on crée un nouveau point de rotation qu'on met à jour sur les axes de rotation de la porte
	FRotator newRotation(GetOwner()->GetActorRotation().Pitch,curveFloatValue,GetOwner()->GetActorRotation().Roll);
	this->GetOwner()->SetActorRelativeRotation(newRotation);
}

/****************************************************************************************************
Description : Méthode qui lance la timeline dans un sens ou l'autre selon l'état de la porte -> fermée de base ou bien ouverte
Input : 
Output : None
Note ://
******************************************************************************************************/
void UDoorBalance2::ToogleAndPlayDoor()
{
	//on vérifie dans un premier temps que la timeline n'est pas déjà en cours d'animation
	if(!timeline.IsPlaying())
	{ //si non on vérifie par un booléen mis à jour à chaque frame dans TickComponent -> CompareMassToBalance si la porte est ouverte ou fermée
		if(isDoorOpen)
		{
			timeline.Play();
			if (GEngine != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(7, 5, FColor::Blue,TEXT("ToogleAndPlayDoorOk"));
			}
			
		}
		else
		{
			timeline.Reverse();
		}
	}
	
}

