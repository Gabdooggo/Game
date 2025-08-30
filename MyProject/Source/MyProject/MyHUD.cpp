// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "Blueprint/UserWidget.h"

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


