// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WG_MainMenu_CPP.generated.h"

/**
 * 
 */
UCLASS()
class CYCLE_3_BXLS_NL_2021_API UWG_MainMenu_CPP : public UUserWidget
{
	GENERATED_BODY()
	
	virtual bool Initialize();
		
	UPROPERTY(meta = (BindWidget))
	UButton* startGame;
	UPROPERTY(meta = (BindWidget))
	UButton* quitGame;

	UFUNCTION()
	void StartButtonClicked();
	UFUNCTION()
	void QuitButtonClicked();
	
};
