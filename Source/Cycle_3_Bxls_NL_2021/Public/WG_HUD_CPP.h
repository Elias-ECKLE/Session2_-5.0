// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "triggerHUD.h"

#include "WG_HUD_CPP.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class CYCLE_3_BXLS_NL_2021_API UWG_HUD_CPP : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize();
	UFUNCTION(BlueprintCallable)
	void GetTriggersZone(UtriggerHUD* triggerConsigne2, UtriggerHUD* triggerMsgEnd);
	UFUNCTION(BlueprintCallable)
	void freezeOpacityTextBlock();
	UFUNCTION(BlueprintCallable)
	void ChangeOpacityText(float opacityTextBlock, float opacityBackgroundTextBlock);
	UFUNCTION(BlueprintCallable)
	void DisplayConsignes1();
	UFUNCTION(BlueprintCallable)
	void DisplayConsignes2();
	UFUNCTION(BlueprintCallable)
	void DisplayMsgEndGame();

	UPROPERTY(meta = (BindWidget))
	 UTextBlock* consignesTextBlock;
	UPROPERTY(meta = (BindWidget))
	UBorder* backgroundTextBlock;


private :
	UPROPERTY()
	UtriggerHUD* triggerZoneConsigne2;
	UPROPERTY()
	UtriggerHUD* triggerZoneMsgEnd;
	UPROPERTY()
	float timerDelay;
	UPROPERTY()
	FTimerHandle UnusedHandle;
	UPROPERTY()
	float opacityText;
	UPROPERTY()
	float opacityBackground;
	UPROPERTY()
	FText consignes1;
	UPROPERTY()
	FText consignes2;
	UPROPERTY()
	FText msgFin;
	
};
