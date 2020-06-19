

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"

#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* IntigatedBY, AActor* DamageCauser);

	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health", meta = (AllowPrivateAccess = "true"))
	float DefaultHealth = 100.0f;
	
	float Helath = 0.0f;

	AActor* MyOwner;

	ATankGameModeBase* GameModeRef;
};
