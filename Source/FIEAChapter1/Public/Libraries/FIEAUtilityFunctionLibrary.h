// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/Object.h"
#include "FIEAUtilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FIEACHAPTER1_API UFIEAUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	//Exposed function for getting CDO to BP
	UFUNCTION(BlueprintCallable, Category = "FIEA", meta = (DeterminesOutputType = "ClassToGet"))
	static UObject* GetClassCDO(UClass* ClassToGet);
};

