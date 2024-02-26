// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/FIEAAbilitySystemComponent.h"

void UFIEAAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UFIEAGameplayEffect> CurrentEffectClass : StartingEffects)
	{
		const FGameplayEffectContextHandle NewContext;
		UFIEAGameplayEffect* CurrentGE = NewObject<UFIEAGameplayEffect>(this, CurrentEffectClass);

		UFIEAAbilitySystemComponent::ApplyGameplayEffectToSelf(CurrentGE, 0.f, NewContext);
	}
}