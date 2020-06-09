


#include "LaunchPad.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
 	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(75,75,50));
	RootComponent = OverlapComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	OverlapComp->SetHiddenInGame(false);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::HandleOverlap);
	
	LaunchSpeed = 1500;
	LaunchPitchAngle = 35.0f;
	
}

void ALaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	FRotator LaunchPadDirection = GetActorRotation();
	LaunchPadDirection.Pitch +=LaunchPitchAngle;
	FVector LaunchPadVelocity = LaunchPadDirection.Vector() * LaunchSpeed;

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter)
	{
		OtherCharacter->LaunchCharacter(LaunchPadVelocity, true,true);
		
		UGameplayStatics::PlaySound2D(this, LaunchPadSound);
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchPadVelocity, NAME_None, true);

		UGameplayStatics::PlaySound2D(this, LaunchPadSound);

	}
		
	
	
}



