// Fill out your copyright notice in the Description page of Project Settings.


#include "AssasinActor.h"
#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputAction.h"

// Sets default values
AAssasinActor::AAssasinActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    AssasinAbilities = CreateDefaultSubobject<UAssasinAbilities>(TEXT("AssasinAbilities"));

}

// Called when the game starts or when spawned
void AAssasinActor::BeginPlay()
{
	Super::BeginPlay();
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    MyCharacter = Cast<AMyCharacter>(Player);
	
}

// Called every frame
void AAssasinActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAssasinActor::AssasinDash()
{
    MyCharacter->HP -= 50;
    UE_LOG(LogTemp, Warning, TEXT("AssasinDash did activate"));
}
