// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class AMyCharacter;

UCLASS()
class MYPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
    
    UPROPERTY(EditAnywhere, Category = "Gold")
    int32 Gold = 200;
    
    UPROPERTY(EditAnywhere, Category = "Health")
    int32 HP = 100;
    
    UPROPERTY(EditAnywhere, Category = "Combat")
    float Damage = 100;
    
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    bool bInvin = false;
    
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    float Timer = 0.f;
    
    UFUNCTION(BlueprintCallable)
    void Dead();
    
    UFUNCTION(BlueprintCallable)
    void TakeDamageFromPlayer();
    
    UFUNCTION(BlueprintCallable)
    void DealDamageToPlayer();
    
    UPROPERTY(EditAnywhere, Category = "References")
    AMyCharacter* MyCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
