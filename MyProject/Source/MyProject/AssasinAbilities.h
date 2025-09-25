// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "AssasinAbilities.generated.h"

class AMyCharacter;
class UInputAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT_API UAssasinAbilities : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAssasinAbilities();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    UFUNCTION(BlueprintCallable)
    void AssasinDash();
        
    UFUNCTION(BlueprintCallable)
    void Assasin(UEnhancedInputComponent* Input);
    
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* IA_Dash;
    
    UPROPERTY(EditAnywhere, Category = "References")
    AMyCharacter* MyCharacter;
    
    UFUNCTION(BlueprintCallable)
    void SetupBindings(UEnhancedInputComponent* Input);

		
};
