// Fill out your copyright notice in the Description page of Project Settings.


#include "WG_MainMenu_CPP.h"

#include "Components/Button.h"

bool UWG_MainMenu_CPP::Initialize()
{
	Super::Initialize();
	
	
	startGame->OnClicked.AddDynamic(this,&UWG_MainMenu_CPP::StartButtonClicked);
	quitGame->OnClicked.AddDynamic(this,&UWG_MainMenu_CPP::QuitButtonClicked);
	return true;


	
}

void UWG_MainMenu_CPP::StartButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("ButtonPlayClicked"));
	UGameplayStatics::OpenLevel(GetWorld(), "Level");
}

void UWG_MainMenu_CPP::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
}
