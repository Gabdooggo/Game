// Fill out your copyright notice in the Description page of Project Settings.
#include "Assasin.h"
#include "MyCharacter.h"

void AAssasin::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
    {
        Input->BindAction(IA_Dash, ETriggerEvent::Started, this, &AAssasin::AssasinDash);
    }
}

void AAssasin::Assasin()
{
    Super::SetupInputComponent();
    
    if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
    {
        Input->BindAction(IA_Dash, ETriggerEvent::Started, this, &AAssasin::AssasinDash);
    }
}

void AAssasin::AssasinDash()
{
    MyCharacter->HP = 50;
    UE_LOG(LogTemp, Warning, TEXT("AssasinDash did activate"));
}

void AAssasin::BeginPlay()
{
    Super::BeginPlay();
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    MyCharacter = Cast<AMyCharacter>(Player);
}

void AAssasin::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
