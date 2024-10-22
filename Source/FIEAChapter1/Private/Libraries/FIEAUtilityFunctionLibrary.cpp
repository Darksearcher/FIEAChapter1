// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/FIEAUtilityFunctionLibrary.h"

const UObject* UFIEAUtilityFunctionLibrary::GetClassCDO(const UClass* ClassToGet)
{
	if (!IsValid(ClassToGet))
	{
		return NULL;
	}
	
	return ClassToGet->GetDefaultObject();

	//Safe way to return if at runtime
	//return NewObject<UObject>(nullptr, ClassToGet);
}