// Fill out your copyright notice in the Description page of Project Settings.


#include "AssasinAbilities.h"
#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "AssasinActor.h"
#include "InputAction.h"

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
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    MyCharacter = Cast<AMyCharacter>(Player);
    Owner = Cast<AAssasinActor>(GetOwner());
    
	
}


// Called every frame
void UAssasinAbilities::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UAssasinAbilities::SetupBindings(UEnhancedInputComponent* Input)
{
    if (Input)
    {
        Input->BindAction(Owner->IA_Dash, ETriggerEvent::Started, Owner, &AAssasinActor::AssasinDash);
    }
}
