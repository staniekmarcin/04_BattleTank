


#include "PaintingPicker.h"

#include "VR_LightPainter/Saving/PainterSaveGameIndex.h"
#include "VR_LightPainter/Saving/PainterSaveGame.h"

#include "ActionBar.h"

//#include "PaintingGrid.h"

APaintingPicker::APaintingPicker()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintingGrid"));
	PaintingGrid->SetupAttachment(GetRootComponent());

	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(GetRootComponent());
}


void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();
	
	UActionBar* ActionBarWidget = Cast<UActionBar>(ActionBar->GetUserWidgetObject());
	if (ActionBarWidget)
	{
		ActionBarWidget->SetParentPicker(this);
	}

	RefreshSlots();
}

int32 APaintingPicker::GetNumberOfPages() const
{
	if (!GetPaintingGrid()) return 0;

	int32 TotalNumberOfSlots = UPainterSaveGameIndex::Load()->GetSlotNames().Num();
	int32 SlotPerPage = GetPaintingGrid()->GetNumberOfSlots();
	
	return FMath::CeilToInt((float)TotalNumberOfSlots / SlotPerPage);
}

void APaintingPicker:: RefreshSlots()
{
	UE_LOG(LogTemp, Warning, TEXT("Number Of pages %d: "), GetNumberOfPages());

	if (!GetPaintingGrid()) return;

	GetPaintingGrid()->AddPaginationDot(true);
	GetPaintingGrid()->AddPaginationDot(false);
	GetPaintingGrid()->AddPaginationDot(false);

	GetPaintingGrid()->ClearPaintings();

	int32 Index = 0;
	for (FString SlotName : UPainterSaveGameIndex::Load()->GetSlotNames())
	{
		GetPaintingGrid()->AddPainting(Index, SlotName);
		++Index;
	}
}

void APaintingPicker::AddPainting()
{
	UPainterSaveGame::Create();

	RefreshSlots();
}

void APaintingPicker::ToggleDeleteMode()
{
	if (!GetPaintingGrid()) return;

	GetPaintingGrid()->ClearPaintings();
}

