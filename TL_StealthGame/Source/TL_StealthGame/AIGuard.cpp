


#include "AIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

AAIGuard::AAIGuard()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGuard::OnPawnSeen);

}

void AAIGuard::BeginPlay()
{
	Super::BeginPlay();
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAIGuard::OnNoiseHeard); // In BeginPlay cause some bug

}

void AAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{	
		return;
	}
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);
}

void AAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Blue, false, 10.0f);
	UE_LOG(LogTemp, Log, TEXT("HEAR YOU"));
}

void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



