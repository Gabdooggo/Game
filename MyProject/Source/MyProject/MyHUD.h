// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "MyHUD.generated.h"

class AMyCharacter;
class UInputMappingContext;
class UInputAction;
class UCanvasPanel;
class UProgressBar;
class UTextBlock;
class UEditableTextBox;
class UCanvasPanelSlot;
class UButton;
class UCheckBox;
class UPanelWidget;
class UButtonSlot;
class AAssasinActor;
class UImage;

UCLASS()
class MYPROJECT_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()
    
public:
    
    UPROPERTY()
    bool bCrossHair = false;
    
    UPROPERTY()
    bool escape = false;
    
    UPROPERTY()
    int32 ZCounter;
    
    UPROPERTY()
    int32 Current;
    
    UPROPERTY()
    float Location = 1100.f;;
    
    UPROPERTY(meta = (BindWidget))
    UButton* Abilities;
    
    UPROPERTY(meta = (BindWidget))
    UButton* Map;
    
    UPROPERTY(meta = (BindWidget))
    UButton* AssasinCheck;
    
    UPROPERTY(meta = (BindWidget))
    UButton* LifeSteal;
    
    UPROPERTY(meta=(BindWidget))
    UProgressBar* HealthBar;
    
    UPROPERTY(meta=(BindWidget, EditAnywhere))
    UTextBlock* Gold;
    
    UPROPERTY(meta=(BindWidget, EditAnywhere))
    UImage* CrossHairI;
    
UPROPERTY(meta=(BindWidget, EditAnywhere))
    UCanvasPanel* RootCanvas;
    
    UPROPERTY(meta=(BindWidget, EditAnywhere))
    UCanvasPanel* AbilitiesCanvas;
    
    UPROPERTY(meta=(BindWidget, EditAnywhere))
    UCanvasPanel* AssasinAbilities;
    
    UPROPERTY(EditAnywhere)
    bool bHovered = false;
    
    UPROPERTY(EditAnywhere)
    bool Tab = true;
    
    UPROPERTY()
    bool IsTab;
    
    UPROPERTY()
    float Mark = 0.f;
    
    UFUNCTION(BlueprintCallable)
    void ZOrder();
    
    UFUNCTION(BlueprintCallable)
    void UpdateHealthBar();
    
    UFUNCTION(BlueprintCallable)
    int32 GetHP() const;
    
    UFUNCTION(BlueprintCallable)
    int32 GetMaxHP() const;
    
    UFUNCTION(BlueprintCallable)
    void Golds();
    
    UFUNCTION(BlueprintCallable)
    void UnHovered();
    
    UFUNCTION(BlueprintCallable)
    void Hovered();
    
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    virtual void NativeOnInitialized() override;
    
    UFUNCTION(BlueprintCallable)
    void Menu();
    
    UFUNCTION(BlueprintCallable)
    void esc();
    
    UFUNCTION(BlueprintCallable)
    void AbilitiesM();
    
    UFUNCTION(BlueprintCallable)
    void MapM();
    
    UFUNCTION(BlueprintCallable)
    void AbilitiesF();
    
    UFUNCTION()
    void References();
    
    UFUNCTION(BlueprintCallable)
    void AssasinAbility();
    
    UFUNCTION(BlueprintCallable)
    void CrossHair();
    
    UPROPERTY(EditAnywhere, Category="Components")
    AAssasinActor* AssasinActor;
    
private:
    UPROPERTY(EditAnywhere, Category = "References")
    AMyCharacter* MyCharacter;
    
    UPROPERTY()
    APawn* PlayerPawn;
	
};
