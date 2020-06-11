

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

class USkeletalMeshComponent;
class UParticleSystem;

UCLASS()
class TL_COOPGAME_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASWeapon();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	TSubclassOf<UDamageType> DamageType;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Weapon")
    FName TracerTargetName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
    UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
    UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
    UParticleSystem* FleshImpactEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
    UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<UCameraShake> FireCamShake;

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFiredTime;

	// Bullets per minnute fired
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float RateOfFire;

	// Derived from RateOffFire
	float TimeBetweenShots;
	
public:
	virtual void Fire();

	void StartFire();
	
	void StopFire();
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float BaseDamage;

	void PlayFireEffects(FVector TracerEndPoint);
};
