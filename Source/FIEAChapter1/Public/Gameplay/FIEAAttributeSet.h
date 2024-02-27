// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "FIEAAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class FIEACHAPTER1_API UFIEAAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	//~ Helper functions for "Health" attributes
	ATTRIBUTE_ACCESSORS(UFIEAAttributeSet, MaxHealth);

	ATTRIBUTE_ACCESSORS(UFIEAAttributeSet, Health);

	ATTRIBUTE_ACCESSORS(UFIEAAttributeSet, Stamina);
	
	ATTRIBUTE_ACCESSORS(UFIEAAttributeSet, Mana);

	ATTRIBUTE_ACCESSORS(UFIEAAttributeSet, MaxSpeed);

	ATTRIBUTE_ACCESSORS(UFIEAAttributeSet, Slipping);

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Mana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Slipping;
};
