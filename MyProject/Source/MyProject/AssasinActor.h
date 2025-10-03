// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AssasinAbilities.h"
#include "AssasinActor.generated.h"

class UAssasinAbilities;
class UInputAction;
class AMyCharacter;
UCLASS()
class MYPROJECT_API AAssasinActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAssasinActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    UPROPERTY(EditAnywhere, Category = "References")
    UAssasinAbilities* AssasinAbilities;
    
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* IA_Dash;
    
    UPROPERTY(EditAnywhere, Category = "References")
    AMyCharacter* MyCharacter;
    
    UFUNCTION(BlueprintCallable)
    void AssasinDash();
    
    UPROPERTY(EditAnywhere)
    bool bEquipped = true;
    

};
