// Fill out your copyright notice in the Description page of Project Settings.
#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SetReplicates(true);
    // Create and set mesh
  
    Root = CreateDefaultSubobject<USceneComponent>("Root");
       SetRootComponent(Root);

       GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>("GunMesh");
       GunMesh->SetupAttachment(Root);
    
    // Create and attach muzzle
    MuzzleLocation = CreateDefaultSubobject<USkeletalMeshComponent>("MuzzleLocation");
    MuzzleLocation->SetupAttachment(GunMesh);
    MuzzleLocation->SetRelativeLocation(FVector(0.f, 50.f, 10.f));
    
    

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
    Super::BeginPlay();
    CurrentAmmo = MaxAmmo;}
    
    void AGun::Fire(){
        CurrentAmmo--;
        ApplyRecoil();
        if(CurrentAmmo <= 0){
            CurrentAmmo = 0;
        }
        // 1. Spawn projectile
        if(ProjectileClass){
            FVector Location = MuzzleLocation->GetComponentLocation();
            FRotator Rotation = MuzzleLocation->GetComponentRotation();
            
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            GetWorld()->SpawnActor<AActor>(ProjectileClass, Location, Rotation, SpawnParams);
        }
        if(MuzzleFlash){
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, MuzzleLocation->GetComponentTransform());
        }
        if(MuzzleSound){
            UGameplayStatics::PlaySoundAtLocation(this, MuzzleSound, GetActorLocation());
        }
        // Raycast for damage
        FHitResult Hit;
        FVector Start = GunMesh->GetSocketLocation("Muzzle");
        FVector End = Start + (GetActorForwardVector() * 10000.0f);
        
        FCollisionQueryParams TraceParams;
        TraceParams.AddIgnoredActor(this);
        TraceParams.AddIgnoredActor(GetOwner());
        
        if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams)){
            AActor* HitActor = Hit.GetActor();
            if(HitActor){
                UGameplayStatics::ApplyDamage(HitActor, DamagePerShot,
                                              GetInstigatorController(), this, UDamageType::StaticClass());
            }
        }
    }
        void AGun::ApplyRecoil(){
            if (APawn* OwnerPawn = Cast<APawn>(GetOwner())){
                if (APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController())){
                    float RecoilPitch = FMath::RandRange(RecoilPitchMin, RecoilPitchMax);
                    float RecoilYaw = FMath::RandRange(RecoilYawMin, RecoilYawMax);
                    PC->AddPitchInput(RecoilPitch);
                    PC->AddYawInput(RecoilYaw);
                }
            }
        }
    

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AGun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AGun, CurrentAmmo);
}



