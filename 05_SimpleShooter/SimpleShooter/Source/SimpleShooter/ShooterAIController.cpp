


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr) return;
    
    MoveToActor(PlayerPawn, 200);
}

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr) return;

    SetFocus(PlayerPawn);

    // TODO turn off focus when AI is dead
    // TODO change focus after getting to AcceptanceRadius
   }
