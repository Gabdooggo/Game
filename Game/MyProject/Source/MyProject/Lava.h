// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Lava.generated.h"

class AMyCharacter;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class MYPROJECT_API ALava : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALava();
    
    UPROPERTY()
    bool bbBurning = false;
    
    UPROPERTY()
    float BTimer = 0.f;
    
    UPROPERTY(EditAnywhere, Category = "Damage")
    float BDamage = 10;
    
    UPROPERTY()
    bool OnFire = false;
    
    UPROPERTY(EditAnywhere, Category = "Damage")
    float LDamage = 25.0;
    
    UFUNCTION()
    void Damage();
    
    UFUNCTION(BlueprintCallable)
    void Burning(float DeltaTime);
    
    UPROPERTY(EditAnywhere, Category = "References")
    AMyCharacter* MyCharacter;
    
    UPROPERTY(EditAnywhere, Category = "References", meta=(EditInline))
        UStaticMeshComponent* LavaMesh;
    
    UPROPERTY()
    UBoxComponent* LavaCollisions;

    UPROPERTY()
    APawn* PlayerPawn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
