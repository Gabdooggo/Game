// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "EnemyAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "MyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    //Optional automatically Possess AI controller when placed in world
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AEnemyAI::StaticClass();
    
    // Set some basic movement values
    GetCharacterMovement()->MaxWalkSpeed = 500.f;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    MyCharacter = Cast<AMyCharacter>(Player);
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::DealDamageToPlayer()
{
    if(MyCharacter && EnemyAI)
    {
        if(!MyCharacter->bInvin)
        {
            
                MyCharacter->HP -= Damage;
                MyCharacter->bInvin = true;}
                
            }
}

void AEnemyCharacter::TakeDamageFromPlayer()
{
    if(MyCharacter && EnemyAI)
    {
        if(!bInvin)
        {
            HP -= MyCharacter->Damage;
            bInvin = true;
        }
    }
}

void AEnemyCharacter::Invincible(float DeltaTime)
{
    if(bInvin)
    {
        Timer += DeltaTime;
        if(Timer >= 0.5f)
        {
            bInvin = false;
            Timer = 0.f;
        }
    }
}

void AEnemyCharacter::Dead()
{
    if(EnemyAI && MyCharacter && HP <= 0)
    {
        EnemyAI->Perceive = false;
        EnemyAI->Dead = true;
        MyCharacter->Gold += Gold;
    }
}
