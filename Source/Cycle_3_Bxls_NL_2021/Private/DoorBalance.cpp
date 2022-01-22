
#include "DoorBalance.h"

#include <string>

//--------------------------------Defaults methods-----------------------------------------
UDoorBalance::UDoorBalance()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	flt_MassMax = 150.f;
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

	//on check constamment si la masse de la triggerZone est supérieure ou non à sa limite fixée, si oui alors on lance l'animation 
	//de la porte avec la timeline 
	CompareBalanceToMaxMass();
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
		triggerVolumeInstance->triggerVolumeBeginCollision.AddDynamic(this,&UDoorBalance::AddBalanceMass);
		triggerVolumeInstance->triggerVolumeEndCollision.AddDynamic(this,&UDoorBalance::SoustrBalanceMass);
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("triggerVolumeInstance Not Found"));
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
		/*
		if (GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(5, 10, FColor::Red, TEXT("Curve float non initialisée"));
		}
		UE_LOG(LogTemp, Error, TEXT("Curve float non init, veuillez l'ajouter dans BP_OpenDoor -> DoorBalance"));
		*/
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

			/*
			if (GEngine != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(7, 5, FColor::Blue,TEXT("ToogleAndPlayDoorOk"));
			}*/
		}
		else
		{
			timeline.Reverse();
		}
	}
	
}



//----------------------------------------------------balance Mass----------------------------------------------------
/****************************************************************************************************
Description : Methode qui fait le lien avec les autres lorsque on ajoute un objet dans la triggerZone
Input : acteur en collision avec la trigger zone -> issue du delegate triggerVolumeBeginCollision dans la classe TriggerVolume_Door.h
Output : None
Note ://
******************************************************************************************************/
void UDoorBalance::AddBalanceMass(AActor* otherActor)
{
	float flt_massActor = GetMassFromObjectCollided(otherActor);
	UpdateMass(flt_massActor,true);
}

/****************************************************************************************************
Description : Idem mais lorqu'un objet sort de la triggerZone
Input : acteur en collision avec la trigger zone -> issue du delegate triggerVolumeEndCollision dans la classe TriggerVolume_Door.h
Output : None
Note ://
******************************************************************************************************/
void UDoorBalance::SoustrBalanceMass(AActor* otherActor)
{
	float flt_massActor = GetMassFromObjectCollided(otherActor);
	UpdateMass(flt_massActor,false);
}

/****************************************************************************************************
Description : Methode qui récupère la masse des objets entrés ou sorti de la triggerZone
Input : acteur en collision avec la trigger zone -> issue du delegate triggerVolumeBeginCollision ou triggerVolumeEndCollision
Output : float mass
Note ://
******************************************************************************************************/
float UDoorBalance::GetMassFromObjectCollided(AActor* actor)
{
	if(ensure(actor))
	{
		UStaticMeshComponent* actorMesh = actor->FindComponentByClass<UStaticMeshComponent>();
		float flt_massActor = 0.f;
	
		if(ensure(actorMesh))
		{
			flt_massActor = actorMesh->GetMass();
			//UE_LOG(LogTemp, Warning, TEXT("Static mesh actor collided find"));
			return flt_massActor;
		}
		else
		{
			/*
			if (GEngine != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(7, 10, FColor::Red, TEXT("Not Static mesh actor collided"));
			}
			UE_LOG(LogTemp, Error, TEXT("Static mesh actor not find"));
			*/
		}
	}
	else
	{
		/*
		if (GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(7, 10, FColor::Red, TEXT("Not actor collided"));
		}
		UE_LOG(LogTemp, Error, TEXT("Actor not find"));
		*/
	}
	return 0.f;
}

/****************************************************************************************************
Description : Méthode qui met à jour la quantité de masse dans la triggerZone
Input : reçoit la nouvelle masse à soit ajouter, soit enlever + bool 
Output : None

Note ://
******************************************************************************************************/
void UDoorBalance::UpdateMass(float flt_valueOperate, bool isIncrm)
{
	isIncrm ? flt_BalanceMass+= flt_valueOperate : flt_BalanceMass-= flt_valueOperate;

	/*
	if (GEngine != nullptr)
	{
		FString theFloatStr = FString::SanitizeFloat(flt_BalanceMass);
		GEngine->AddOnScreenDebugMessage(6, 5, FColor::Blue, theFloatStr);
	}
	*/
}

/****************************************************************************************************
Description : On compare la quantité de masse dans la triggerZone par rapport au maximum fixé
Input :
Output : None

Note ://
******************************************************************************************************/
void UDoorBalance::CompareBalanceToMaxMass()
{
	flt_BalanceMass>flt_MassMax ? isDoorOpen=true : isDoorOpen=false;
	ToogleAndPlayDoor();
}





