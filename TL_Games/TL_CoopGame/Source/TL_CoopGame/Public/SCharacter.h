#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ASWeapon;

UCLASS()
class TL_COOPGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacter();

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void BeginCrouch();
	void EndCrouch();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* SpringArmComp;

	bool bWantsToZoom;
	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.0, ClampMax = 100))
	float ZoomInterpSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float ZommedFOV;
	float DefaultFOV;
	void BeginZoom();
	void EndZoom();

	ASWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly,Category="Player")
	TSubclassOf<ASWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly,Category="Player")
	FName WeaponAttachSockeTName;
	
	void StartFire();
	void StopFire();
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

};
