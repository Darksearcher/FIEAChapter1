// MyAbilityTask_PlayMontageNotify.cpp

#include "Gameplay/Task/FIEA_PlayMontageAndWaitForEvent.h"
#include "FIEAChapter1/FIEAChapter1Character.h"
#include "AbilitySystemGlobals.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemLog.h"
#include "AbilitySystemGlobals.h"


UFIEA_PlayMontageAndWaitForEvent* UFIEA_PlayMontageAndWaitForEvent::FIEACreatePlayMontageAndWaitForEvent(UGameplayAbility* OwningAbility,
    FName NewTaskInstanceName, UAnimMontage* NewMontageToPlay, float NewRate, FName NewStartSection, bool bNewStopWhenAbilityEnds, float NewAnimRootMotionTranslationScale, float NewStartTimeSeconds, bool bNewAllowInterruptAfterBlendOut)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(NewRate);

	UFIEA_PlayMontageAndWaitForEvent* MyObj = NewAbilityTask<UFIEA_PlayMontageAndWaitForEvent>(OwningAbility, NewTaskInstanceName);
	MyObj->MontageToPlay = NewMontageToPlay;
	MyObj->Rate = NewRate;
	MyObj->StartSection = NewStartSection;
	MyObj->AnimRootMotionTranslationScale = NewAnimRootMotionTranslationScale;
	MyObj->bStopWhenAbilityEnds = bNewStopWhenAbilityEnds;
	MyObj->bAllowInterruptAfterBlendOut = bNewAllowInterruptAfterBlendOut;
	MyObj->StartTimeSeconds = NewStartTimeSeconds;

	return MyObj;
}

void UFIEA_PlayMontageAndWaitForEvent::Activate()
{
	if (Ability == nullptr)
	{
		return;
	}

	bool bPlayedMontage = false;

	if (UAbilitySystemComponent* ASC = AbilitySystemComponent.Get())
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();		

		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			// Playing a montage could potentially fire off a callback into game code which could kill this ability! Early out if we are  pending kill.
			if (ShouldBroadcastAbilityTaskDelegates() == false)
			{
				return;
			}			

			AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UFIEA_PlayMontageAndWaitForEvent::OnPlayFIEAMontageNotifyBegin);
			AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &UFIEA_PlayMontageAndWaitForEvent::OnPlayFIEAMontageNotifyEnd);
		}	
	}    
	
	Super::Activate();
}
FPlayMontageAnimNotifyDelegate OnPlayMontageNotifyEnd;
void UFIEA_PlayMontageAndWaitForEvent::OnPlayFIEAMontageNotifyBegin(FName TheNotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	NotifyName = TheNotifyName;
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnNotifyBegin.Broadcast(TheNotifyName);
	}	
}

void UFIEA_PlayMontageAndWaitForEvent::OnPlayFIEAMontageNotifyEnd(FName TheNotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	NotifyName = TheNotifyName;
	OnNotifyEnd.Broadcast(TheNotifyName);
}