

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alerted
};
UCLASS()
class TL_STEALTHGAME_API AAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	AAIGuard();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator OriginRotation;
	void ResetOrientation();
	FTimerHandle TimerHandle_ResetOrientation;

	EAIState AIGuardState;
	void SetAIGuardState(EAIState NewState);
	UFUNCTION(BlueprintImplementableEvent, Category="AI")
	void OnStateChange(EAIState NewState);

	UPROPERTY(EditInstanceOnly,Category="AI")
    bool bPatrol;

	UPROPERTY(EditInstanceOnly, Category="AI", meta = (EditCondition = "bPatrol"))
    AActor* FirstPatrolPoint;
	UPROPERTY(EditInstanceOnly, Category="AI", meta = (EditCondition = "bPatrol"))
    AActor* SecondPatrolPoint;

	AActor* CurrentPatrolPoint;
	void MovetoNextPatrolPoint();
public:	
	virtual void Tick(float DeltaTime) override;

};


