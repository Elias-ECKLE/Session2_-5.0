


#include "TriggerVolume_Door2.h"

#include <string>


UTriggerVolume_Door2::UTriggerVolume_Door2()
{

	PrimaryComponentTick.bCanEverTick = true;

	flt_massMax=200.f;
	isTriggerZoneCompleted=false;
}


// Called when the game starts
void UTriggerVolume_Door2::BeginPlay()
{
	Super::BeginPlay();
	SetupBoxCollider();
	
}


// Called every frame
void UTriggerVolume_Door2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CompareBalanceToMassMax();
}


//---------------------------------------------------trigger zone---------------------------------------------------------

void UTriggerVolume_Door2::SetupBoxCollider()
{
	boxCollider = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (ensure(boxCollider))
	{
		UE_LOG(LogTemp, Warning, TEXT("Box collider Component find"));
		//comme OnOverlapBegin et OnEndOverlap agissent comme des custom event dynamiques, il faut leur ajouter un AddDynamic
		boxCollider->OnComponentBeginOverlap.AddDynamic(this,&UTriggerVolume_Door2::OnOverlapBegin);
		boxCollider->OnComponentEndOverlap.AddDynamic(this,&UTriggerVolume_Door2::OnOverlapEnd);
	}
}



void UTriggerVolume_Door2::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AddMassTriggerZone(OtherActor);
}

void UTriggerVolume_Door2::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SoustrMassTriggerZone(OtherActor);
}




//-----------------------------------------------comparison mass--------------------------------------------
void UTriggerVolume_Door2::AddMassTriggerZone(AActor* actor)
{
	float flt_massActor = GetMassFromObjectCollided(actor);
	UpdateMass(flt_massActor,true);
}

void UTriggerVolume_Door2::SoustrMassTriggerZone(AActor* actor)
{
	float flt_massActor = GetMassFromObjectCollided(actor);
	UpdateMass(flt_massActor,false);
}

void UTriggerVolume_Door2::UpdateMass(float flt_valueOperate, bool isIncrm)
{
	isIncrm ? flt_massActuelle+= flt_valueOperate : flt_massActuelle-= flt_valueOperate;

	if (GEngine != nullptr)
	{
		FString theFloatStr = FString::SanitizeFloat(flt_massActuelle);
		GEngine->AddOnScreenDebugMessage(6, 5, FColor::Blue, theFloatStr);
	}
}

float UTriggerVolume_Door2::GetMassFromObjectCollided(AActor* actor)
{
	if(ensure(actor))
	{
		UStaticMeshComponent* actorMesh = actor->FindComponentByClass<UStaticMeshComponent>();
		float flt_massActor = 0.f;
	
		if(ensure(actorMesh))
		{
			flt_massActor = actorMesh->GetMass();
			UE_LOG(LogTemp, Warning, TEXT("Static mesh actor collided find"));
			return flt_massActor;
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
	return 0.f;
}

void UTriggerVolume_Door2::CompareBalanceToMassMax()
{
	FString IntAsString = FString::FromInt(int_Tag);
	if(flt_massActuelle>=flt_massMax)
	{
		if(isTriggerZoneCompleted==false)
		{
			isTriggerZoneCompleted=true;
			triggerCompletedTag.Broadcast(int_Tag);
			UE_LOG(LogTemp, Warning, TEXT("TriggerZone%s Completed"),*IntAsString);
		}
	}

}


