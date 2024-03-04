// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Abilities/GameplayAbility.h"
#include "InputAction.h"
#include "AbilityDataMapping.generated.h"

/**
 * 
 */
UCLASS()
class FIEACHAPTER1_API UAbilityDataMapping : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	TArray<TSubclassOf<UGameplayAbility>> GetPassiveAbilities();
	TMap<UInputAction*, TSubclassOf<UGameplayAbility>> GetActiveAbilities();

private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>> PassiveAbilities;

	UPROPERTY(EditAnywhere)
	TMap<UInputAction*, TSubclassOf<UGameplayAbility>> ActiveAbilities;

};
