// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/FIEAUtilityFunctionLibrary.h"

UObject* UFIEAUtilityFunctionLibrary::GetClassCDO(UClass* ClassToGet)
{
	return ClassToGet->GetDefaultObject();
}