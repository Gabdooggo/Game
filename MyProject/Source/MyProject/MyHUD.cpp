// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "MyCharacter.h"

void UMyHUD::NativeConstruct()
{
    Super::NativeConstruct();
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    MyCharacter = Cast<AMyCharacter>(Player);
    UpdateHealthBar();
    Golds();
}


void UMyHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    UpdateHealthBar();
    Golds();
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
    int32 Amount = 0;
    if(MyCharacter)
    {
        Amount = MyCharacter->Gold;
    }
    Gold->SetText(FText::AsNumber(Amount));
}

//void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
   // Super::SetupPlayerInputComponent(PlayerInputComponent);
    
   // if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
   // {
   //  Input->BindAction(HUDInstance->IA_Tab, ETriggerEvent::Triggered, HUDInstance, &UMyHUD::Menu);
   // }
//}


void UMyHUD::Menu()
{
    RootCanvas->SetRenderTranslation(FVector2D(0.f, 1.f));
    
    RootCanvas->SetRenderTransform(FWidgetTransform(
           FVector2D(0.f, 1.f),   // Translation (X,Y)
           FVector2D(1.f, 1.f),     // Scale
           FVector2D(0.f, 0.f),     // Shear
           0.f // Angle (deg)
       ));
    UE_LOG(LogTemp, Warning, TEXT("Menu is working"));
}

