// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Gun.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnemyAI.h"
#include "EnemyCharacter.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "MyHud.h"
using namespace std;

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Spring arm
        SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
        SpringArm->SetupAttachment(RootComponent);
        SpringArm->TargetArmLength = 500.f;
        SpringArm->bUsePawnControlRotation = true;

        // Follow camera
       Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
       Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
       Camera->bUsePawnControlRotation = false;

        bUseControllerRotationYaw = false;
        GetCharacterMovement()->bOrientRotationToMovement = true;
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
   if(EnemyCharacter){
       EnemyAI = Cast<AEnemyAI>(EnemyCharacter->GetController());}
    
    if(!EnemyAI && !EnemyCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI did not take any damage"));
    }
    
    if (APlayerController* PC = Cast<APlayerController>(Controller))
       {
           if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
           {
               Subsystem->AddMappingContext(MappingContext, 0);
               Subsystem->AddMappingContext(Assasin, 1);
               Subsystem->AddMappingContext(HUD, 2);
               
           }
       }

    
    if (!Controller && GetWorld())
    {
        GetWorld()->GetFirstPlayerController()->Possess(this);
    }
    
    if (GetController() && GetController()->IsPlayerController())
    {
        UE_LOG(LogTemp, Warning, TEXT("Possessed by player controller"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Not possessed by player controller!"));
    }
    
    
    if (GunClass)
        {
            CurrentGun = GetWorld()->SpawnActor<AGun>(GunClass);
            CurrentGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_r_socket"));
            CurrentGun->SetOwner(this);
        }
	
}

void AMyCharacter::Invincibility(float DeltaTime)
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

void AMyCharacter::Burn(float DeltaTime)
{
    if(bBInvin)
    {
        BTimer += DeltaTime;
        if(BTimer >= 0.5f)
        {
            bBInvin = false;
            BTimer = 0.f;
        }
    }
}

void AMyCharacter::Death()
{
    if(HP <= 0)
    {
        AController* MyController = GetController();
        if (MyController)
        {
            MyController->UnPossess();
            Dead = true;
        }
    }
}


void AMyCharacter::OnFire()
{
    if (CurrentGun)
    {
        CurrentGun->Fire();
    }
}

void AMyCharacter::StartFiring()
{
    // Prevent multiple timers
        if (!GetWorld()->GetTimerManager().IsTimerActive(FireTimer))
        {
            OnFire(); // Fire immediately
            GetWorld()->GetTimerManager().SetTimer(
                FireTimer,
                this,
                &AMyCharacter::OnFire,
                FireRate,
                true
            );
        }
}

void AMyCharacter::StopFiring()
{
    GetWorld()->GetTimerManager().ClearTimer(FireTimer);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Death();
    Invincibility(DeltaTime);
    Burn(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
        Input->BindAction(IA_Fire, ETriggerEvent::Started, this, &AMyCharacter::StartFiring);
        Input->BindAction(IA_Fire, ETriggerEvent::Completed, this, &AMyCharacter::StopFiring);
        Input->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
        Input->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
        //Input->BindAction(IA_Jump, ETriggerEvent::Started, this, &AMyCharacter::Jumps);
        Input->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
        Input->BindAction(IA_Dash, ETriggerEvent::Triggered, this, &AMyCharacter::Dash);
        if(HUDInstance){
            Input->BindAction(HUDInstance->IA_Tab, ETriggerEvent::Triggered, HUDInstance, &UMyHUD::Menu);
        }
    }
}
    
    void AMyCharacter::Move(const FInputActionValue& Value)
    {
        FVector2D MovementVector = Value.Get<FVector2D>();
        FRotator Rotation = Controller->GetControlRotation();
        FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
        FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(ForwardDirection, MovementVector.Y);
        FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
    
    void AMyCharacter::Look(const FInputActionValue& Value)
    {
        if (Controller != nullptr){
            FVector2D LookAxis = Value.Get<FVector2D>();
            AddControllerYawInput(LookAxis.X);
            AddControllerPitchInput(LookAxis.Y);
        }
    }
    
    void AMyCharacter::Jumps()
    {
        
    }
    
    void AMyCharacter::Dash()
    {
        if(!Dashes) return;
        if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        {
            AnimInstance->Montage_Play(Dashes, 0.2f);
            
        }
        
        
    };



