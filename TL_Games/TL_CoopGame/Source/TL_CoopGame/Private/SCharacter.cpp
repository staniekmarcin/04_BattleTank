

#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "SWeapon.h"

ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	ZommedFOV = 65;
	ZoomInterpSpeed = 20;

	WeaponAttachSockeTName = "WeaponSocket";
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultFOV = CameraComp->FieldOfView;

	//SpawnDefaultWeapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	CurrentWeapon = GetWorld()->SpawnActor<ASWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSockeTName);
	}
}

void ASCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void ASCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void ASCharacter::BeginCrouch()
{
	Crouch();
}

void ASCharacter::EndCrouch()
{
	UnCrouch();
}

void ASCharacter::BeginZoom()
{
	bWantsToZoom = true;
}

void ASCharacter::EndZoom()
{
	bWantsToZoom = false;
}

void ASCharacter::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}

void ASCharacter::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}

void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Lerping camera when lerping //
	float TargetFOV = bWantsToZoom ? ZommedFOV : DefaultFOV;
	float NewFOV = FMath::FInterpTo(CameraComp->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);
	CameraComp->SetFieldOfView(NewFOV);
}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward" , this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight" , this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp" , this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn" , this, &ASCharacter::AddControllerYawInput);
	
	PlayerInputComponent->BindAction("Crouch" ,IE_Pressed, this, &ASCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch" , IE_Released, this, &ASCharacter::EndCrouch);
	
	PlayerInputComponent->BindAction("Jump" , IE_Pressed, this, &ACharacter::Jump);
	
	PlayerInputComponent->BindAction("Zoom" , IE_Pressed, this, &ASCharacter::BeginZoom);
	PlayerInputComponent->BindAction("Zoom" , IE_Released, this, &ASCharacter::EndZoom);
	
	PlayerInputComponent->BindAction("Fire" , IE_Pressed, this, &ASCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire" , IE_Released, this, &ASCharacter::StopFire);

	//PlayerInputComponent->BindAction("Fire" , IE_Pressed, this, &ASCharacter::BeginZoom);


}

FVector ASCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}