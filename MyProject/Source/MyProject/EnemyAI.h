// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAI.generated.h"

class AMyCharacter;
class AEnemyCharacter;

UCLASS()
class MYPROJECT_API AEnemyAI : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAI();
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
        UBehaviorTree* BehaviorTreeAsset;
    
    UFUNCTION()
    virtual void OnPossess(APawn* InPawn) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    UFUNCTION(BlueprintCallable, Category = "AI")
    void MoveToPlayer(APawn* PlayerPawn);
    
public:
    
    UPROPERTY(VisibleAnywhere, Category = "Health")
    bool Dead = false;
    
    UPROPERTY(EditDefaultsOnly, Category = "Perception")
    UAIPerceptionComponent* EnemyPerceptionComponent;
    
    UPROPERTY(EditDefaultsOnly, Category = "Perception")
    UAISenseConfig_Sight* SightConfig;
    
    UFUNCTION(BlueprintCallable, Category = "Damage")
    void TakeDamageFromPlayer(float DeltaTime);
   
    UFUNCTION(BlueprintCallable, Category = "AI")
    void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);
    
    UFUNCTION(BlueprintCallable, Category = "Damage")
    void DealDamageToPlayer();
    
    UFUNCTION(BlueprintCallable, Category = "Health")
    void Death();
  
    UFUNCTION(BlueprintCallable, Category = "Kill")
    void Kill();
    
    UFUNCTION(BlueprintImplementableEvent, Category = "MyEvents")
    void MyBlueprintEvent();
    
    UPROPERTY(VisibleAnywhere, Category = "Perception")
    bool Perceive = false;
    
    UFUNCTION(BlueprintCallable, Category = "Perception")
    void StartPatrolling();
    
    UFUNCTION(BlueprintCallable, Category = "Perception")
    void MoveToNextPatrolPoint();
    
protected:
    
    FTimerHandle PatrolTimerHandle;
    
    UPROPERTY(EditAnywhere, Category = "Perception")
    float PatrolRadius = 1000.f;
    
    UPROPERTY(EditAnywhere, Category = "Perception")
    float PatrolDelay = 3.f;
    
private:
    UPROPERTY(VisibleAnywhere)
    AMyCharacter* MyCharacter;
    
    UPROPERTY(VisibleAnywhere)
    AEnemyCharacter* EnemyCharacter;
    

};
