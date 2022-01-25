// Fill out your copyright notice in the Description page of Project Settings.


#include "WG_HUD_CPP.h"

#include "Components/TextBlock.h"


bool UWG_HUD_CPP::Initialize()
{
	Super::Initialize();

	opacityText=100.f;
	opacityBackground=0.70;
	timerDelay=15.f;
	ChangeOpacityText(0.f, 0.f);
	

	consignes1 = FText::FromString(ANSI_TO_TCHAR("Objectif : Placer au centre l'objet le plus dore de la piece"));
	consignes2 = FText::FromString(ANSI_TO_TCHAR("Objectif : Atteindre les 200kg d'objets dans les 3 zones centrales. Attention tous les objets ne peuvent pas etre deplaces"));
	msgFin = FText::FromString(ANSI_TO_TCHAR("Bravo, vous avez atteint la fin du jeu. Veuillez avancer tout droit pour revenir à l'ecran-titre"));

	DisplayConsignes1();
	return true;
}

void UWG_HUD_CPP::GetTriggersZone(UtriggerHUD* triggerConsigne2, UtriggerHUD* triggerMsgEnd)
{
	
	if(ensure(triggerConsigne2))
	{
		UE_LOG(LogTemp, Warning, TEXT("getTriggersZoneActivated_Consigne2"));
		triggerZoneConsigne2=triggerConsigne2;
		triggerZoneConsigne2->hud.AddDynamic(this,&UWG_HUD_CPP::DisplayConsignes2);
	}
	if(ensure(triggerMsgEnd))
	{
		UE_LOG(LogTemp, Warning, TEXT("getTriggersZoneActivated_MsgEnd"));
		triggerZoneMsgEnd=triggerMsgEnd;
		triggerZoneMsgEnd->hud.AddDynamic(this,&UWG_HUD_CPP::DisplayMsgEndGame);
	}
}


void UWG_HUD_CPP::ChangeOpacityText(float opacityTextBlock, float opacityBackgroundTextBlock)
{
	consignesTextBlock->SetOpacity(opacityTextBlock);
	backgroundTextBlock->SetRenderOpacity(opacityBackgroundTextBlock);
}
void UWG_HUD_CPP::freezeOpacityTextBlock()
{
	ChangeOpacityText(0.f, 0.f);
}


void UWG_HUD_CPP::DisplayConsignes1()
{
	UE_LOG(LogTemp, Warning, TEXT("consignes 1 chargees"));
	consignesTextBlock->SetText(consignes1);
	ChangeOpacityText(opacityText, opacityBackground);
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &UWG_HUD_CPP::freezeOpacityTextBlock,timerDelay , false);
}
void UWG_HUD_CPP::DisplayConsignes2()
{
	UE_LOG(LogTemp, Warning, TEXT("consignes 2 chargees"));
	consignesTextBlock->SetText(consignes2);
	ChangeOpacityText(opacityText, opacityBackground);
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &UWG_HUD_CPP::freezeOpacityTextBlock,timerDelay , false);
}
void UWG_HUD_CPP::DisplayMsgEndGame()
{
	UE_LOG(LogTemp, Warning, TEXT("msg fin charge"));
	consignesTextBlock->SetText(msgFin);
	ChangeOpacityText(opacityText, opacityBackground);
}




