

#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SPickupActor.generated.h"

UCLASS()
class TL_COOPGAME_API ASPickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASPickupActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereComponent* SphereComp;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UDecalComponent* DecalComp;

	UPROPERTY(EditInstanceOnly, Category="PickupActor")
	TSubclassOf<ASPowerupActor> PowerupClass;

	ASPowerupActor* PowerupInstance;
	
	UPROPERTY(EditDefaultsOnly, Category="PickupActor")
	float CooldownDuration;

	FTimerHandle TimerHandle_RespawnTimer;
	
	void Respawn();
public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
