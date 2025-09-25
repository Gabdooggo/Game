// Fill out your copyright notice in the Description page of Project Settings.


#include "AssasinAbilities.h"
#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
UAssasinAbilities::UAssasinAbilities()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAssasinAbilities::BeginPlay()
{
    Super::BeginPlay();
    
	
}


// Called every frame
void UAssasinAbilities::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAssasinAbilities::AssasinDash()
{
    MyCharacter->HP = 50;
    UE_LOG(LogTemp, Warning, TEXT("AssasinDash did activate"));
}

void UAssasinAbilities::Assasin(UEnhancedInputComponent* Input)
{
    if(Input)
    {
        Input->BindAction(IA_Dash, ETriggerEvent::Started, this, &UAssasinAbilities::AssasinDash);
    }
}

void UAssasinAbilities::SetupBindings(UEnhancedInputComponent* Input)
{
    if (Input)
    {
        Input->BindAction(IA_Dash, ETriggerEvent::Started, this, &UAssasinAbilities::AssasinDash);
    }
}
