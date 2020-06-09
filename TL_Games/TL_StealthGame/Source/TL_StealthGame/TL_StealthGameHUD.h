// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TL_StealthGameHUD.generated.h"

UCLASS()
class ATL_StealthGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATL_StealthGameHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

