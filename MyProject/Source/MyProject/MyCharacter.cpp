// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Gun.h"
#include "Assasin.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnemyAI.h"
#include "EnemyCharacter.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "MyHud.h"
#include "AssasinAbilities.h"
#include "AssasinActor.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"

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
    
    MappingContexts();
    
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

void AMyCharacter::MappingContexts()
{
    if (APlayerController* PC = Cast<APlayerController>(Controller))
       {
           if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
           {
               Subsystem->AddMappingContext(MappingContext, 0);
               if(AssasinAbility && bAssasinB)
               {
                   Subsystem->AddMappingContext(Assasin, 1);
                   UE_LOG(LogTemp, Warning, TEXT("AssasinActor did equip"))
                   
               }
               Subsystem->AddMappingContext(HUD, 2);
               
           }
       }
}

void AMyCharacter::InitAbilityRef()
{
    // If not set in the editor, find one at runtime (pick one strategy):
    if (!AssasinActor)
    {
        // A) first actor of that class in the level
        AssasinActor = Cast<AAssasinActor>(
                                           UGameplayStatics::GetActorOfClass(this, AAssasinActor::StaticClass()));}
    // B) or find by tag you placed on the actor
    // TArray<AActor*> Found;
    // UGameplayStatics::GetAllActorsWithTag(this, FName("AbilityOwner"), Found);
    // AbilityActorRef = Found.Num() ? Cast<AAssasinActor>(Found[0]) : nullptr;
    if(!AssasinAbility && AssasinActor)
    {
        AssasinAbility = AssasinActor->FindComponentByClass<UAssasinAbilities>();
        UE_LOG(LogTemp, Warning, TEXT("AssasinActor is not null"));}
    if(AssasinAbility)
    {
        UE_LOG(LogTemp, Warning, TEXT("AssasinAbility is not null"));
        bAssasin = true;
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("AssasinAbility is nulldd"));
    }
    
   if (APlayerController* PC = Cast<APlayerController>(GetController()))
  {
      if(HUDClass)
      {
          // No Blueprint needed: use the C++ class directly
          HUDInstance = CreateWidget<UMyHUD>(PC, HUDClass);
      }
      if (HUDInstance)
      {
          HUDInstance->References();
          HUDInstance->AddToViewport();
      }
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

void AMyCharacter::Cursor()
{
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if(bTab)
        {
                FInputModeGameAndUI InputMode;
                PC->bEnableClickEvents = true;
                PC->bShowMouseCursor = true;
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                if (HUDInstance)                        // the same instance you AddToViewport()
                {
                    InputMode.SetWidgetToFocus(HUDInstance->TakeWidget());
                }
                PC->SetInputMode(InputMode);
        }
        if(!bTab)
        {
                PC->bShowMouseCursor = false;
                PC->SetInputMode(FInputModeGameOnly());
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
    MappingContexts();
    Death();
    Invincibility(DeltaTime);
    Burn(DeltaTime);
    Cursor();
    if(DashC != 0.f)
    {
        DashC -= DeltaTime;
    }
    if(DashT >= 0.f)
    {
        DashT -= DeltaTime;
        Movement = false;
        
    }
    else if(DashT <= 0.f)
    {
        Movement = true;
    }
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
        Input->BindAction(IA_Dash, ETriggerEvent::Started, this, &AMyCharacter::Dash);
        Input->BindAction(IA_RightClick, ETriggerEvent::Started, this, &AMyCharacter::Aim);
            if (!AssasinAbility && !AssasinActor)
            {
                // References
                InitAbilityRef();
            }
            if(AssasinAbility && AssasinActor)
            {
                UE_LOG(LogTemp, Warning, TEXT("AssasinAbility is not null"));
                AssasinAbility->SetupBindings(Input);
            }
            else {
                UE_LOG(LogTemp, Warning, TEXT("AssasinAbility is null"));
            }
        if(HUDInstance){
            Input->BindAction(IA_Tab, ETriggerEvent::Triggered, HUDInstance, &UMyHUD::Menu);
            Input->BindAction(IA_esc, ETriggerEvent::Triggered, HUDInstance, &UMyHUD::esc);
        }
        else if(!HUDInstance){
            UE_LOG(LogTemp, Warning, TEXT("HUDInstance is null"));
        }
    }
}
    
    void AMyCharacter::Move(const FInputActionValue& Value)
    {
        if(Movement)
        {
            FVector2D MovementVector = Value.Get<FVector2D>();
            FRotator Rotation = Controller->GetControlRotation();
            FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
            FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
            AddMovementInput(ForwardDirection, MovementVector.Y);
            FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
            AddMovementInput(RightDirection, MovementVector.X);
        }
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
        Dashe = true;
        if(DashC <= 0.0f)
        {
            if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
            {
                const FVector Dir = GetActorForwardVector();
                const float Speed = 2400.f;
                AnimInstance->Montage_Play(Dashes, 1.f);
               LaunchCharacter(Dir * Speed, true, false);
                DashC = 0.5f;
                DashT = 0.5f;
                Dashe = false;
                
            }
        }
        
        
    }

void AMyCharacter::Aim()
{
    HUDInstance->bCrossHair = true;
    UE_LOG(LogTemp, Warning, TEXT("Right Click/Aim does work"));
}
    
    void AMyCharacter::references()
    {
        
    };



