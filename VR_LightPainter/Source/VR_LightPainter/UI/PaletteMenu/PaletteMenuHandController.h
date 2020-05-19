

#pragma once

#include "CoreMinimal.h"
#include "VR_LightPainter/HandControllerBase.h"

#include "Components/WidgetComponent.h"

#include "PaletteMenuHandController.generated.h"

/**
 * 
 */
UCLASS()
class VR_LIGHTPAINTER_API APaletteMenuHandController : public AHandControllerBase
{
	GENERATED_BODY()
	
public:

	APaletteMenuHandController();

private:

	// Components
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PaletteMenu;

};
