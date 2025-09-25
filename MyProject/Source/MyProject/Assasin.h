// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "Assasin.generated.h"

class AMyCharacter;

UCLASS()
class MYPROJECT_API AAssasin : public APlayerController
{
	GENERATED_BODY()
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

    
    UFUNCTION()
    void AssasinDash();
        
    UFUNCTION()
    void Assasin();
    
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* IA_Dash;
    
    UPROPERTY(VisibleAnywhere, Category = "References")
    AMyCharacter* MyCharacter;
	
};
