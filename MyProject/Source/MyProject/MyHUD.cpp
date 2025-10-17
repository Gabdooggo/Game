// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "AssasinActor.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "MyCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/CheckBox.h"

void UMyHUD::NativeConstruct()
{
    Super::NativeConstruct();
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    MyCharacter = Cast<AMyCharacter>(Player);
    References();
    UpdateHealthBar();
    Golds();
    AbilitiesF();
}

void UMyHUD::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    
}

void UMyHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    References();
    UpdateHealthBar();
    Golds();
    AbilitiesF();
    if (AssasinCheck && AssasinCheck->IsHovered())
    {
        UE_LOG(LogTemp, Verbose, TEXT("Checkbox hovered"));
    }
}

void UMyHUD::UpdateHealthBar()
{
    if(!HealthBar) return;
    const int32 HP = GetHP();
    const int32 MaxHP = GetMaxHP();
    float Percent = 0.f;
    if(MyCharacter->MaxHP > 0)
    {
        Percent = FMath::Clamp(static_cast<float>(MyCharacter->HP) / static_cast<float>(MyCharacter->MaxHP), 0.f, 1.f);
    }
    HealthBar->SetPercent(Percent);
}

int32 UMyHUD::GetHP() const
{
    if(MyCharacter)
    {
        return MyCharacter->HP;
    }
    return 0;
}

int32 UMyHUD::GetMaxHP() const
{
    if(MyCharacter)
    {
        return MyCharacter->MaxHP;
    }
    return 0;
}

void UMyHUD::Golds()
{
    if(Gold)
    {
        int32 Amount = 0;
        if(MyCharacter)
        {
            Amount = MyCharacter->Gold;
        }
        Gold->SetText(FText::AsNumber(Amount));
    }
}

void UMyHUD::AssasinAbility()
{
    
    MyCharacter->bAssasinB = true;
}

void UMyHUD::Hovered()
{
    AssasinCheck->SetBackgroundColor(FLinearColor(0.503f, 0.503f, 0.503f, 1.0f)); // RGBA 0–1
    LifeSteal->SetBackgroundColor(FLinearColor(0.503f, 0.503f, 0.503f, 1.0f)); // RGBA 0–1
}

void UMyHUD::UnHovered()
{
    AssasinCheck->SetBackgroundColor(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f)); // RGBA 0–1
    LifeSteal->SetBackgroundColor(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f)); // RGBA 0–1
}

//void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
   // Super::SetupPlayerInputComponent(PlayerInputComponent);
    
   // if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
   // {
   //  Input->BindAction(HUDInstance->IA_Tab, ETriggerEvent::Triggered, HUDInstance, &UMyHUD::Menu);
   // }
//}

void UMyHUD::AbilitiesM()
{
    UE_LOG(LogTemp, Warning, TEXT("Abilities button was pressed"));
    Location = 2250.f;
    Mark -= 1;
    Menu();
}

void UMyHUD::MapM()
{
    UE_LOG(LogTemp, Warning, TEXT("Maps button was pressed"));
    Location = 1100.f;
    Mark -= 1;
    Menu();
}

void UMyHUD::Menu()
{
    Mark += 1;
    if (!RootCanvas)
    {
        UE_LOG(LogTemp, Warning, TEXT("Menu(): RootCanvas is null"));
        return;
    }
    if(Mark <= 1)
    {
    
        if (UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(RootCanvas->Slot))
        {
            // Make positioning absolute (top-left) so X/Y works predictably
            Slot->SetAnchors(FAnchors(0.f, 0.f, 0.f, 0.f));
            Slot->SetAlignment(FVector2D(0.f, 0.f));       // pivot at top-left
            Slot->SetAutoSize(false);
            // Move the child canvas (pixels)
            FVector2D pos = Slot->GetPosition();
            pos.Y = 1100.f;
            pos.X += 0.f;                                // e.g., slide right 200
            pos.Y -= Location; // e.g., down 100
            Slot->SetPosition(pos);
            MyCharacter->bTab = true;
            IsTab = true;
            // ✅ Show or hide mouse cursor and input mode
        }
    }
    if(Mark > 1)
    {
        Tab = false;
    }
    
    if(!Tab)
    {
        if (UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(RootCanvas->Slot))
        {
            // Make positioning absolute (top-left) so X/Y works predictably
            Slot->SetAnchors(FAnchors(0.f, 0.f, 0.f, 0.f));
            Slot->SetAlignment(FVector2D(0.f, 0.f));       // pivot at top-left
            Slot->SetAutoSize(false);
            
            // Move the child canvas (pixels)
            FVector2D pos = Slot->GetPosition();
            pos.X += 0.f;                                // e.g., slide right 200
            pos.Y += Location;                                // e.g., down 100
            Slot->SetPosition(pos);
            Mark = 0.f;
            Tab = true;
            MyCharacter->bTab = false;
            Location = 1100.f;
            IsTab = false;
            
        }
    }
}

void UMyHUD::esc()
{
    if(IsTab)
    {
        if(Current == 0)
        {
            MapM();
            //Menu();
        }
        else{
            
        }
        escape = true;
        ZOrder();
        escape = false;
    }
    else{
        
    }
}

void UMyHUD::AbilitiesF()
{
    if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(AssasinCheck->Slot))
       {
           if(AssasinActor && AssasinActor->bequipped)
           {
            CanvasSlot->SetZOrder(1);
           }
           else{
               CanvasSlot->SetZOrder(0);
               
                }
       }
    //if(UPanelWidget* Parent = AssasinCheck->GetParent())
   // {
       // if(MyCharacter && MyCharacter->bequipped)
       // {
            //AssasinCheck->RemoveFromParent();
       // }
 //   }
   // else{
        
   // }
}

void UMyHUD::ZOrder()
{
    if(UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(AssasinAbilities->Slot))
    {
        if(!escape)
        {
            Current = 1;
            Slot->SetZOrder(Current);
        }
        
        else if(escape)
        {
            Current = 0;
            Slot->SetZOrder(Current);
        }
    }
    
}

void UMyHUD::References()
{
    if (!AssasinActor && MyCharacter)
    {
        AssasinActor = MyCharacter->AssasinActor;
    }
}
