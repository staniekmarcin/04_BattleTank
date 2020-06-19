


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* IntigatedBY, AActor* DamageCauser)
{
	
}

