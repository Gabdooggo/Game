// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "MyHUD.generated.h"

class AMyCharacter;
class UInputMappingContext;
class UInputAction;
class UCanvasPanel;

UCLASS()
class MYPROJECT_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()
    
public:
    UPROPERTY(meta=(BindWidget))
    UProgressBar* HealthBar;
    
    UPROPERTY(meta=(BindWidget, EditAnywhere))
    UTextBlock* Gold;
    
    UPROPERTY(Meta=(BindWidget, EditAnywhere))
    UCanvasPanel* RootCanvas;
    
    UFUNCTION(BlueprintCallable)
    void UpdateHealthBar();
    
    UFUNCTION(BlueprintCallable)
    int32 GetHP() const;
    
    UFUNCTION(BlueprintCallable)
    int32 GetMaxHP() const;
    
    UFUNCTION(BlueprintCallable)
    void Golds();
    
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    
    UPROPERTY(EditAnywhere, Category = "MappingContext")
    UInputMappingContext* HUD;
    
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* IA_Tab;
    
    
    UFUNCTION(BlueprintCallable)
    void Menu();
    IN
    
private:
    UPROPERTY(EditAnywhere, Category = "References")
    AMyCharacter* MyCharacter;
    
    UPROPERTY()
    APawn* PlayerPawn;
    
	
};
