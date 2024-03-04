// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AbilityDataMapping.h"

TArray<TSubclassOf<UGameplayAbility>> UAbilityDataMapping::GetPassiveAbilities()
{
	return PassiveAbilities;

}


TMap<UInputAction*, TSubclassOf<UGameplayAbility>> UAbilityDataMapping::GetActiveAbilities()
{
	return ActiveAbilities;
}