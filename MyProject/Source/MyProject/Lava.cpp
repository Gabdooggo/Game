// Fill out your copyright notice in the Description page of Project Settings.


#include "Lava.h"
#include "MyCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ALava::ALava()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALava::BeginPlay()
{
	Super::BeginPlay();
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    MyCharacter = Cast<AMyCharacter>(Player);
    TArray<UActorComponent*> TaggedComps = GetComponentsByTag(UBoxComponent::StaticClass(), FName("LavaBox"));
    OnFire = false;
    if (TaggedComps.Num() > 0){
        LavaCollisions = Cast<UBoxComponent>(TaggedComps[0]);
    }
    if(MyCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("MyCharacter works"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MyCharacter does not work"));
    }
    if(LavaCollisions)
    {
        UE_LOG(LogTemp, Warning, TEXT("Lava is Active"));
    }
    else{
        UE_LOG(LogTemp, Warning, TEXT("Lava is InActive"));
    }
    if(PlayerPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerPawn is working"))
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerPawn isn't working"))
    }
    
	
}

void ALava::Burning(float DeltaTime)
{
    if(!MyCharacter->bBInvin && MyCharacter)
    {
        MyCharacter->bBInvin = true;
        MyCharacter->HP-=BDamage;
    }
    BTimer += DeltaTime;
    if(BTimer >= 10.0f)
    {
        bbBurning = false;
        BTimer = 0.f;
    }
}

void ALava::Damage()
{
    if(MyCharacter && !MyCharacter->bBInvin)
    {
        MyCharacter->bBInvin = true;
        MyCharacter->HP-=LDamage;
    }
}

// Called every frame
void ALava::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(IsValid(PlayerPawn) && IsValid(LavaCollisions)){
        if(LavaCollisions->IsOverlappingActor(PlayerPawn)){
            OnFire = true;
        }
        if((OnFire || bbBurning) && !LavaCollisions->IsOverlappingActor(PlayerPawn)){
            OnFire = false;
            bbBurning = true;
            Burning(DeltaTime);
        }}
    if(OnFire && MyCharacter){
        Damage();
    }

}

