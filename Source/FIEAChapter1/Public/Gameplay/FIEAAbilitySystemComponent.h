// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Gameplay/FIEAGameplayEffect.h"
#include "EnhancedInputComponent.h"
#include "AbilityDataMapping.h"
#include "FIEAAbilitySystemComponent.generated.h"

class UInputAction;

USTRUCT()
struct FAbilityInputBinding
{
	GENERATED_BODY()

	int32  InputID = 0;
	uint32 OnPressedHandle = 0;
	uint32 OnReleasedHandle = 0;
	TArray<FGameplayAbilitySpecHandle> BoundAbilitiesStack;
};

/**
 * 
 */
UCLASS()
class FIEACHAPTER1_API UFIEAAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTagChangeDelegate, FGameplayTag, MyGameplayTag, bool, bMyBool);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FIEA|Starting GAS");
	TArray<TSubclassOf<UFIEAGameplayEffect>> StartingEffects;

	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void SetInputBinding(UInputAction* InputAction, FGameplayAbilitySpecHandle AbilityHandle);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void ClearInputBinding(FGameplayAbilitySpecHandle AbilityHandle);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void ClearAbilityBindings(UInputAction* InputAction);

	UPROPERTY(BlueprintAssignable, Category = "FIEA")
	FTagChangeDelegate OnTagChanged;

	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;

private:
	void OnAbilityInputPressed(UInputAction* InputAction);

	void OnAbilityInputReleased(UInputAction* InputAction);

	void RemoveEntry(UInputAction* InputAction);

	void TryBindAbilityInput(UInputAction* InputAction, FAbilityInputBinding& AbilityInputBinding);

	void InitializeGameplayEffects();

	void InitializeGameplayAbilities();

	FGameplayAbilitySpec* FindAbilitySpec(FGameplayAbilitySpecHandle Handle);

	virtual void BeginPlay() override;

	UPROPERTY(transient)
	TMap<UInputAction*, FAbilityInputBinding> MappedAbilities;

	UPROPERTY(transient)
	UEnhancedInputComponent* InputComponent;

	UPROPERTY(EditAnywhere, Category = "FIEA|Starting GAS")
	TArray<UAbilityDataMapping*> MyStartingAbilitySets;
};
