


#include "PainterSaveGame.h"

#include "Kismet/GameplayStatics.h"

UPainterSaveGame* UPainterSaveGame::Create()
{
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StaticClass());
	return Cast<UPainterSaveGame>(NewSaveGame);
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, TEXT("TEST Save"), 0);
}