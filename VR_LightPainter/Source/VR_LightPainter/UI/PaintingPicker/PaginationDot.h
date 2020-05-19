

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "PaginationDot.generated.h"

/**
 * 
 */
UCLASS()
class VR_LIGHTPAINTER_API UPaginationDot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetActive(bool bActive);
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UImage* DotImage;

private:
	// Configuration
	UPROPERTY(EditDefaultsOnly)
	float DisabledOpacity = 0.3f;
};
