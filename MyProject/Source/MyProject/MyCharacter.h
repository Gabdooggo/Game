// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.generated.h"

class UMyHUD;
class USpringArmComponent;
class UCameraComponent;
class AGun;
class AEnemyAI;
class UInputMappingContext;
class UInputAction;
class AEnemyCharacter;
class UAnimMontage;
class AAssasin;
class UAssasinAbilities;
class AAssasinActor;

UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
    
    UPROPERTY(EditAnywhere, Category = "Dash")
    float DashC = 0.f;
    UPROPERTY(EditAnywhere, Category = "Dash")
    float DashT = 0.f;
    
    UPROPERTY(EditAnywhere, Category = "Abilities")
    bool bAssasinB = false;
    
    UPROPERTY()
    bool bAssasin = false;
    
    UPROPERTY()
    bool Dashe = false;
    
    UPROPERTY(EditAnywhere, Category = "Burn")
    float BTimer = 0.f;
    
    UPROPERTY(EditAnywhere, Category = "Burn")
    bool bBInvin = false;
    
    UPROPERTY(EditAnywhere, Category = "Health")
    int32 MaxHP = 200;
    
    UPROPERTY(EditAnywhere, Category = "Health")
    int32 HP = 200;
    
    UPROPERTY()
    bool bInvin = false;
    
    UPROPERTY(EditAnywhere, Category = "Health")
    float Timer = 0.f;
    
    UPROPERTY(EditAnywhere)
    int32 Gold = 0;
    
    UPROPERTY(BlueprintReadOnly)
    bool Dead = false;
    
    UPROPERTY(EditAnywhere)
    float FireRate = 0.2f;
    
    UPROPERTY(EditAnywhere, Category = "Combat")
    float Damage = 250.f;
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

        UFUNCTION(BlueprintCallable, Category = "Gun")
        void OnFire();
    FTimerHandle FireTimer;
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Move(const FInputActionValue& Value);
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Look(const FInputActionValue& Value);
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Jumps();
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Dash();
    
    UFUNCTION(BlueprintCallable, Category = "Gun")
    void StopFiring();
    
    UFUNCTION(BlueprintCallable, Category = "Gun")
    void StartFiring();
    
    UFUNCTION(BlueprintCallable, Category = "Health")
    void Invincibility(float DeltaTime);
    
    UFUNCTION(BlueprintCallable, Category = "Burn")
    void Burn(float DeltaTime);
        
    UFUNCTION(BlueprintCallable)
    void Death();
    
    UPROPERTY(EditAnywhere)
    bool Movement = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
    AEnemyCharacter* EnemyCharacter;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
    AEnemyAI* EnemyAI;
    
    UPROPERTY(VisibleAnywhere, Category = "MappingContext")
    UInputMappingContext* HUD;
    
    UPROPERTY(VisibleAnywhere, Category = "UI")
    UMyHUD* HUDInstance;
    
    UPROPERTY(VisibleAnywhere, Category = "UI")
    TSubclassOf<UMyHUD> HUDClass;
    
    UPROPERTY(EditAnywhere, Category = "Abilities")
    AAssasin* Assasins;
    
    UPROPERTY(EditAnywhere, Category="Abilities")
    TSubclassOf<class AAssasin> AssasinControllerClass;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
       UAssasinAbilities* AssasinAbility;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
    AAssasinActor* AssasinActor;
    
    UFUNCTION(BlueprintCallable)
    void InitAbilityRef();
    
    UFUNCTION(BlueprintCallable)
    void MappingContexts();
    
    UFUNCTION()
    void references();
    
    //UPROPERTY(EditAnywhere, Category="UI")
    //TSubclassOf<UMyHUD> HUDClass;
    
    public:
        // Called every frame
        virtual void Tick(float DeltaTime) override;
    
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    
protected:
    UPROPERTY(EditAnywhere)
    USpringArmComponent* SpringArm;
    
    UPROPERTY(EditAnywhere)
    UCameraComponent* Camera;
    
    UPROPERTY(EditDefaultsOnly, Category = "Gun")
    TSubclassOf<AGun> GunClass;
    
    UPROPERTY(EditAnywhere)
    AGun* CurrentGun;
    
    UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimMontage* Dashes;
    
    UPROPERTY(VisibleAnywhere, Category = "Mapping Context")
    UInputMappingContext* MappingContext;
    
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Tab;
    
    UPROPERTY(VisibleAnywhere, Category = "Mapping Context")
    UInputMappingContext* Assasin;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_Dash;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
        UInputAction* IA_Move;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
        UInputAction* IA_Look;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
        UInputAction* IA_Jump;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
        UInputAction* IA_Fire;
    
};
