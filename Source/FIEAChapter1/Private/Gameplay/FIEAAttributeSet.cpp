// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/FIEAAttributeSet.h"
#include "GameplayEffectExtension.h"


void UFIEAAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
    // Remember to call the parent's implementation.
    Super::PostGameplayEffectExecute(Data);

    // Check to see if this call affects our Health by using the Property Getter.
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        // This Gameplay Effect is changing Health. Apply it, but restrict the value first.
        // In this case, Health's base value must be non-negative.
        SetHealth(FMath::Max(GetHealth(), 0.0f));
    }

    if (Data.EvaluatedData.Attribute == GetMaxSpeedAttribute())
    {
        // This Gameplay Effect is changing Health. Apply it, but restrict the value first.
        // In this case, Health's base value must be non-negative.        
        SetMaxSpeed(FMath::Max(GetMaxSpeed(), 0.0f));
    }

    if (Data.EvaluatedData.Attribute == GetSlippingAttribute())
    {
        float ModifiedValue = FMath::RoundToFloat(GetSlipping());
        ModifiedValue = FMath::Clamp(ModifiedValue, 0, 1);
        SetSlipping(ModifiedValue);
    }
}