// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/FIEAAbilitySystemComponent.h"

namespace EnhancedInputAbilitySystem_Impl
{
	constexpr int32 InvalidInputID = 0;
	int32 IncrementingInputID = InvalidInputID;

	static int32 GetNextInputID()
	{
		return ++IncrementingInputID;
	}
}

void UFIEAAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (IsValid(Owner) && Owner->InputComponent) {
		InputComponent = CastChecked<UEnhancedInputComponent>(Owner->InputComponent);
	}

	InitializeGameplayEffects();
	InitializeGameplayAbilities();
}

void UFIEAAbilitySystemComponent::InitializeGameplayEffects()
{
	for (TSubclassOf<UFIEAGameplayEffect> CurrentEffectClass : StartingEffects)
	{
		const FGameplayEffectContextHandle NewContext;
		UFIEAGameplayEffect* CurrentGE = NewObject<UFIEAGameplayEffect>(this, CurrentEffectClass);

		UFIEAAbilitySystemComponent::ApplyGameplayEffectToSelf(CurrentGE, 0.f, NewContext);
	}
}

void UFIEAAbilitySystemComponent::InitializeGameplayAbilities()
{
	for (UAbilityDataMapping* CurrentAbilitySet : MyStartingAbilitySets)
	{
		TArray<TSubclassOf<UGameplayAbility>> CurrentPassiveAbilities = CurrentAbilitySet->GetPassiveAbilities();
		TMap<UInputAction*, TSubclassOf<UGameplayAbility>> CurrentActiveAbilities = CurrentAbilitySet->GetActiveAbilities();

		for (auto& Elem : CurrentActiveAbilities)
		{
			UInputAction* Key = Elem.Key;
			TSubclassOf<UGameplayAbility> Value = Elem.Value;

			FGameplayAbilitySpecHandle CurrentGivenAbility = K2_GiveAbility(Value);
			SetInputBinding(Key, CurrentGivenAbility);
		}	
	}
}

void UFIEAAbilitySystemComponent::SetInputBinding(UInputAction* InputAction, FGameplayAbilitySpecHandle AbilityHandle)
{
	using namespace EnhancedInputAbilitySystem_Impl;

	FGameplayAbilitySpec* BindingAbility = FindAbilitySpec(AbilityHandle);

	FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction);
	if (AbilityInputBinding)
	{
		FGameplayAbilitySpec* OldBoundAbility = FindAbilitySpec(AbilityInputBinding->BoundAbilitiesStack.Top());
		if (OldBoundAbility && OldBoundAbility->InputID == AbilityInputBinding->InputID)
		{
			OldBoundAbility->InputID = InvalidInputID;
		}
	}
	else
	{
		AbilityInputBinding = &MappedAbilities.Add(InputAction);
		AbilityInputBinding->InputID = GetNextInputID();
	}

	if (BindingAbility)
	{
		BindingAbility->InputID = AbilityInputBinding->InputID;
	}

	AbilityInputBinding->BoundAbilitiesStack.Push(AbilityHandle);
	TryBindAbilityInput(InputAction, *AbilityInputBinding);
}

FGameplayAbilitySpec* UFIEAAbilitySystemComponent::FindAbilitySpec(FGameplayAbilitySpecHandle Handle)
{
	FGameplayAbilitySpec* FoundAbility = nullptr;
	FoundAbility = FindAbilitySpecFromHandle(Handle);
	return FoundAbility;
}

void UFIEAAbilitySystemComponent::TryBindAbilityInput(UInputAction* InputAction, FAbilityInputBinding& AbilityInputBinding)
{
	if (InputComponent)
	{
		// Pressed event
		if (AbilityInputBinding.OnPressedHandle == 0)
		{
			AbilityInputBinding.OnPressedHandle = InputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &UFIEAAbilitySystemComponent::OnAbilityInputPressed, InputAction).GetHandle();
		}

		// Released event
		if (AbilityInputBinding.OnReleasedHandle == 0)
		{
			AbilityInputBinding.OnReleasedHandle = InputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &UFIEAAbilitySystemComponent::OnAbilityInputReleased, InputAction).GetHandle();
		}
	}
}

void UFIEAAbilitySystemComponent::OnAbilityInputPressed(UInputAction* InputAction)
{
	using namespace EnhancedInputAbilitySystem_Impl;

	FAbilityInputBinding* FoundBinding = MappedAbilities.Find(InputAction);
	if (FoundBinding && ensure(FoundBinding->InputID != InvalidInputID))
	{
		AbilityLocalInputPressed(FoundBinding->InputID);
	}
}

void UFIEAAbilitySystemComponent::OnAbilityInputReleased(UInputAction* InputAction)
{
	using namespace EnhancedInputAbilitySystem_Impl;

	FAbilityInputBinding* FoundBinding = MappedAbilities.Find(InputAction);
	if (FoundBinding && ensure(FoundBinding->InputID != InvalidInputID))
	{
		AbilityLocalInputReleased(FoundBinding->InputID);
	}
}

void UFIEAAbilitySystemComponent::RemoveEntry(UInputAction* InputAction)
{
	if (FAbilityInputBinding* Bindings = MappedAbilities.Find(InputAction))
	{
		if (InputComponent)
		{
			InputComponent->RemoveBindingByHandle(Bindings->OnPressedHandle);
			InputComponent->RemoveBindingByHandle(Bindings->OnReleasedHandle);
		}

		for (FGameplayAbilitySpecHandle AbilityHandle : Bindings->BoundAbilitiesStack)
		{
			using namespace EnhancedInputAbilitySystem_Impl;

			FGameplayAbilitySpec* AbilitySpec = FindAbilitySpec(AbilityHandle);
			if (AbilitySpec && AbilitySpec->InputID == Bindings->InputID)
			{
				AbilitySpec->InputID = InvalidInputID;
			}
		}

		MappedAbilities.Remove(InputAction);
	}
}

void UFIEAAbilitySystemComponent::ClearInputBinding(FGameplayAbilitySpecHandle AbilityHandle)
{
	using namespace EnhancedInputAbilitySystem_Impl;

	if (FGameplayAbilitySpec* FoundAbility = FindAbilitySpec(AbilityHandle))
	{
		// Find the mapping for this ability
		auto MappedIterator = MappedAbilities.CreateIterator();
		while (MappedIterator)
		{
			if (MappedIterator.Value().InputID == FoundAbility->InputID)
			{
				break;
			}

			++MappedIterator;
		}

		if (MappedIterator)
		{
			FAbilityInputBinding& AbilityInputBinding = MappedIterator.Value();

			if (AbilityInputBinding.BoundAbilitiesStack.Remove(AbilityHandle) > 0)
			{
				if (AbilityInputBinding.BoundAbilitiesStack.Num() > 0)
				{
					FGameplayAbilitySpec* StackedAbility = FindAbilitySpec(AbilityInputBinding.BoundAbilitiesStack.Top());
					if (StackedAbility && StackedAbility->InputID == 0)
					{
						StackedAbility->InputID = AbilityInputBinding.InputID;
					}
				}
				else
				{
					// NOTE: This will invalidate the `AbilityInputBinding` ref above
					RemoveEntry(MappedIterator.Key());
				}
				// DO NOT act on `AbilityInputBinding` after here (it could have been removed)


				FoundAbility->InputID = InvalidInputID;
			}
		}
	}
}

void UFIEAAbilitySystemComponent::ClearAbilityBindings(UInputAction* InputAction)
{
	RemoveEntry(InputAction);
}

void UFIEAAbilitySystemComponent::OnTagUpdated(const FGameplayTag& Tag, bool TagExists)
{
	OnTagChanged.Broadcast(Tag, TagExists);
}