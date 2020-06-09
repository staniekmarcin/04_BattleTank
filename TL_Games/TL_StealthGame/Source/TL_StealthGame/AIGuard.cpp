


#include "AIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TL_StealthGameGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AAIGuard::AAIGuard()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGuard::OnPawnSeen);

	AIGuardState = EAIState::Idle;
}

void AAIGuard::BeginPlay()
{
	Super::BeginPlay();
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAIGuard::OnNoiseHeard); // In BeginPlay cause some bug

	OriginRotation = GetActorRotation();

	if (bPatrol)
	{
		MovetoNextPatrolPoint();
	}
}

void AAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{	
		return;
	}
	DrawDebugSphere(
		GetWorld(),
		SeenPawn->GetActorLocation(),
		32.0f,
		12, FColor::Yellow,
		false,
		10.0f
		);

	ATL_StealthGameGameMode* GM = Cast<ATL_StealthGameGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}

	SetAIGuardState(EAIState::Alerted);
	
	AController* AIController = GetController();
	if (AIController)
	{
		AIController->StopMovement();
	}
}

void AAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (AIGuardState == EAIState::Alerted)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Blue, false, 10.0f);
	UE_LOG(LogTemp, Log, TEXT("HEAR YOU"));

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0;
	NewLookAt.Roll = 0;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(
		TimerHandle_ResetOrientation,
		this,
		&AAIGuard::ResetOrientation,
		3.0f
		);

	SetAIGuardState(EAIState::Suspicious);

	AController* AIController = GetController();
	if (AIController)
	{
		AIController->StopMovement();
	}
}

void AAIGuard::ResetOrientation()
{
	if (AIGuardState == EAIState::Alerted)
	{
		return;
	}
	
	SetActorRotation(OriginRotation);

	SetAIGuardState(EAIState::Idle);

	if (bPatrol)
	{
		MovetoNextPatrolPoint();
	}
}

void AAIGuard::SetAIGuardState(EAIState NewState)
{
	if (AIGuardState == NewState)
	{
		return;
	}
	
	AIGuardState = NewState;

	OnStateChange(AIGuardState);
}

void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentPatrolPoint)
	{
		FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
		float DistanceToGoal = Delta.Size();

		if (DistanceToGoal < 50)
		{
			MovetoNextPatrolPoint();
		}

	}

}

void AAIGuard::MovetoNextPatrolPoint()
{
	if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
	{
		CurrentPatrolPoint = FirstPatrolPoint;
	}
	else
	{
		CurrentPatrolPoint = SecondPatrolPoint;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), CurrentPatrolPoint);
}



