// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAI.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "MyCharacter.h"
#include "BrainComponent.h"
#include "AIController.h"
#include "EnemyCharacter.h"


AEnemyAI::AEnemyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
    
    SightConfig->SightRadius = 1000.f; //The max distance where the AI can see someone
    SightConfig->LoseSightRadius = 1200.f; //The distance where the AI will lose sight of the player
    SightConfig->PeripheralVisionAngleDegrees = 70.f; //The angle where the AI can see someone.
    SightConfig->SetMaxAge(5.f); //How long the AI remembers seeing someone
    
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    
    EnemyPerceptionComponent->ConfigureSense(*SightConfig);
    EnemyPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
    EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAI::OnTargetPerceived);
    
    

}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
    BrainComponent->RestartLogic();
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    MyCharacter = Cast<AMyCharacter>(Player);
    ACharacter* ControlledPawn = Cast<ACharacter>(GetPawn());
    EnemyCharacter = Cast<AEnemyCharacter>(ControlledPawn);
	
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if(EnemyCharacter && MyCharacter){
        if(Perceive){
            APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
            if(PlayerPawn)
            {
                float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetPawn()->GetActorLocation());
                
                if(Distance <= 150.f)
                {
                    DealDamageToPlayer();
                    TakeDamageFromPlayer(DeltaTime);
                    Kill();
                    Death();
                }
            }
            
        }}}

void AEnemyAI::StartPatrolling()
{
    if(EnemyCharacter){
        EnemyCharacter->HP = 200;
    }
}

void AEnemyAI::MoveToNextPatrolPoint()
{
    if(EnemyCharacter){
        EnemyCharacter->Damage = 100;}
}
void AEnemyAI::DealDamageToPlayer()
{
    
    if(MyCharacter && EnemyCharacter)
    {
        if(!MyCharacter->bInvin)
        {
            
                MyCharacter->HP -= EnemyCharacter->Damage;
                MyCharacter->bInvin = true;}
                
            }
            
        }

void AEnemyAI::TakeDamageFromPlayer(float DeltaTime)
{
    if(MyCharacter && EnemyCharacter)
    {
        if(!EnemyCharacter->bInvin)
        {
            EnemyCharacter->HP -= MyCharacter->Damage;
            EnemyCharacter->bInvin = true;
            EnemyCharacter->Timer = 0.f;
        }
        else {
            EnemyCharacter->Timer += DeltaTime;
            if(EnemyCharacter-> Timer >= 0.5f)
            {
                EnemyCharacter->bInvin = false;
                EnemyCharacter->Timer = 0.f;
            }
        }
    }}

void AEnemyAI::Kill()
{
    if(MyCharacter && MyCharacter->Dead)
    {
        Perceive = false;
        EnemyPerceptionComponent->ForgetActor(MyCharacter);
        MyBlueprintEvent();
    }
}

void AEnemyAI::Death()
{
        if(EnemyCharacter && MyCharacter && EnemyCharacter->HP <= 0)
        {
            Perceive = false;
            Dead = true;
            MyCharacter->Gold += EnemyCharacter->Gold;
            MyCharacter->DeathMark += 1;
            }
    if(!EnemyCharacter || !MyCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI did take damage"));
    }
            
        }
    
    
    
    void AEnemyAI::OnPossess(APawn* InPawn)
    {
        Super::OnPossess(InPawn);
        EnemyCharacter;
    }
    
    void AEnemyAI::MoveToPlayer(APawn* PlayerPawn)
    {
        if(PlayerPawn)
        {
            MoveToActor(PlayerPawn, 50.f); //Acceptable Radius
            BrainComponent->StopLogic("Player Detected");
            
        }
    }
    
    void AEnemyAI::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
        if(MyCharacter){
            if(Stimulus.WasSuccessfullySensed() && !MyCharacter->Dead && !Dead)
            {
                MoveToPlayer(Cast<APawn>(Actor));
                Perceive = true;
            }
            else if(!Stimulus.WasSuccessfullySensed() && !Dead) {
                Perceive = false;
                MyBlueprintEvent();
            }
        }}
