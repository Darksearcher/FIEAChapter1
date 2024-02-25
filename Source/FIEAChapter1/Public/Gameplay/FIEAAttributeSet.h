// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "FIEAAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class FIEACHAPTER1_API UFIEAAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	//~ Helper functions for "Health" attributes
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UFIEAAttributeSet, Health);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UFIEAAttributeSet, Stamina);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Stamina);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Stamina);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Stamina);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UFIEAAttributeSet, Mana);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Mana);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Mana);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Mana);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UFIEAAttributeSet, MaxSpeed);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxSpeed);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxSpeed);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxSpeed);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UFIEAAttributeSet, Slipping);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Slipping);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Slipping);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Slipping);

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:
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
