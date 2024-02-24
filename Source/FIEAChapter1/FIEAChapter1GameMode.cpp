// Copyright Epic Games, Inc. All Rights Reserved.

#include "FIEAChapter1GameMode.h"
#include "FIEAChapter1Character.h"
#include "UObject/ConstructorHelpers.h"

AFIEAChapter1GameMode::AFIEAChapter1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
