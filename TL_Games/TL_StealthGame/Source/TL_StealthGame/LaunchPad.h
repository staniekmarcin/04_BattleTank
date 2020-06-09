

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

UCLASS()
class TL_STEALTHGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComp;
	
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* OverlapComp;

	UFUNCTION()
    void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category="Sounds")
    USoundBase* LaunchPadSound;

	UPROPERTY(EditInstanceOnly, Category="LaunchPad")
	float LaunchSpeed;
	UPROPERTY(EditInstanceOnly, Category="LaunchPad")
	float LaunchPitchAngle;

};
