

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class MYPROJECT_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

    UFUNCTION(BluePrintCallable, Category = "Gun")
    void Fire();
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(VisibleAnywhere)
        USkeletalMeshComponent* GunMesh;
    
    UPROPERTY(VisibleAnywhere)
      USceneComponent* Root;
    
    
    // Ammo
        UPROPERTY(EditAnywhere, Category = "Ammo")
    TSubclassOf<AActor> ProjectileClass;
    
        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
        int32 MaxAmmo = 30;

        UPROPERTY(Replicated, VisibleAnywhere, Category = "Ammo")
        int32 CurrentAmmo;

        // Damage
        UPROPERTY(EditDefaultsOnly, Category = "Damage")
        float DamagePerShot = 10.0f;

        // Effects
        UPROPERTY(EditDefaultsOnly, Category = "Effects")
        UParticleSystem* MuzzleFlash;

        UPROPERTY(EditDefaultsOnly, Category = "Effects")
        USoundBase* MuzzleSound;
    
        UPROPERTY(EditDefaultsOnly, Category = "Effects")
    USkeletalMeshComponent* MuzzleLocation;

        // Recoil
        UPROPERTY(EditDefaultsOnly, Category = "Recoil")
        float RecoilPitchMin = -1.0f;

        UPROPERTY(EditDefaultsOnly, Category = "Recoil")
        float RecoilPitchMax = -2.0f;
    
        UPROPERTY(EditDefaultsOnly, Category = "Recoil")
        float RecoilYawMin = -0.5f;

        UPROPERTY(EditDefaultsOnly, Category = "Recoil")
        float RecoilYawMax = 0.5f;

    private:
        UFUNCTION(BluePrintCallable, Category = "Apply_Recoil")
        void ApplyRecoil();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
   
    

};
