// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Gameplay/FIEAGameplayEffect.h"
#include "FIEAAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class FIEACHAPTER1_API UFIEAAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects");
	TArray<TSubclassOf<UFIEAGameplayEffect>> StartingEffects;
};
