// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "GameplayTagsManager.h"
#include "FieaPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class FIEACHAPTER1_API AFieaPlayerStart : public APlayerStart
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Tags, meta = (Categories = "PlayerStart"))
	FGameplayTag GameplayTagFromCode;
};
