
#include "DoorBalance.h"

#include <string>

//--------------------------------Defaults methods-----------------------------------------
UDoorBalance::UDoorBalance()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	str_RefObj = "StaticMeshActor_23";
	isDoorOpen=false;
}


//tous les appels devant se faire au niveau du BeginPlay ont été faits en blueprint dans BP_OpenDoor
void UDoorBalance::BeginPlay()
{
	Super::BeginPlay();
}


void UDoorBalance::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//on fait avancer la timeline de frame en frame
	timeline.TickTimeline(DeltaTime);
}


//--------------------------------------delegate collision trigger--------------------------------------
/****************************************************************************************************
Description : Methode qui récupère l'instance TriggerVolume_Door gérant la triggerZone de la scène
Input : référence de triggerZone
Output : None
Note ://
******************************************************************************************************/
void UDoorBalance::GetTriggerCollision(UTriggerVolume_Door* triggerVolume)
{
	triggerVolumeInstance=triggerVolume;
}
/****************************************************************************************************
Description : Deux custom events ont été mis en place dans TriggerVolume_Door
A partir de l'instance récupérée, on les lie donc à deux méthodes qui seront appelées pour tout objet entrant ou sortant de la triggerZone
Input : 
Output : None
Note ://
******************************************************************************************************/
void UDoorBalance::SetupDelegateTriggerCollision()
{
	if(ensure(triggerVolumeInstance))
	{
		triggerVolumeInstance->triggerVolumeBeginCollision.AddDynamic(this,&UDoorBalance::UDoorBalance::CompareObjectToObjectReference);
		triggerVolumeInstance->triggerVolumeEndCollision.AddDynamic(this,&UDoorBalance::UDoorBalance::CompareObjectToObjectReference);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("triggerVolumeInstance Not Found"));
	}
	
}


//---------------------------------------------animation door--------------------------------------------------
/****************************************************************************************************
Description : Methode qui configure la timeline gérant le mouvement de la porte en fonction d'une courbe de type float -> ouverte ou fermée
Input : 
Output : None
Note ://
******************************************************************************************************/
void UDoorBalance::SetupTimeline()
{
	//si l'élément "float curve" existe alors on met en place le point d'entrée de la timeline
	if(doorCurve)
	{	
		//on crée une variable qui va suivre la progression de la timeline
		FOnTimelineFloat progressFunction;
		//on la lie ensuite à une méthode qu'on va appeler à chaque avancée de la timeline.
		//C'est dans cette timeline qu'on va maj la //rotation de la porte 
		progressFunction.BindUFunction(this,FName("UpdateAnimationDoor"));

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
void UDoorBalance::UpdateAnimationDoor()
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
void UDoorBalance::ToogleAndPlayDoor()
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



//----------------------------------------------------balance Mass----------------------------------------------------

FString UDoorBalance::GetNameFromObjectCollided(AActor* actor)
{
	FString str_NameActor ="";
	if(ensure(actor))
	{
		if(ensure(actor))
		{
			str_NameActor = actor->GetName();
			//UE_LOG(LogTemp, Warning, TEXT("Static mesh actor collided find"));
			UE_LOG(LogTemp, Warning, TEXT("%s"), *str_NameActor);
			return str_NameActor;
		}
		else
		{
			if (GEngine != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(7, 10, FColor::Red, TEXT("Not Static mesh actor collided"));
			}
			UE_LOG(LogTemp, Error, TEXT("Static mesh actor not find"));
		}
	}
	else
	{
		if (GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(7, 10, FColor::Red, TEXT("Not actor collided"));
		}
		UE_LOG(LogTemp, Error, TEXT("Actor not find"));
	}
	return "";
}

void UDoorBalance::CompareObjectToObjectReference(AActor* actor)
{
	str_InstObj = GetNameFromObjectCollided(actor);
	str_InstObj==str_RefObj ? isDoorOpen=true : isDoorOpen=false;
	ToogleAndPlayDoor();
}






