// MyAbilityTask_PlayMontageNotify.h

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "FIEA_PlayMontageAndWaitForEvent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFIEAMontageWaitSimpleDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFIEAMontageNotifyTaskDelegate, FGameplayTag, TheNotify);

UCLASS()
class FIEACHAPTER1_API UFIEA_PlayMontageAndWaitForEvent : public UAbilityTask_PlayMontageAndWait
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintAssignable)
    FFIEAMontageNotifyTaskDelegate OnNotifyBegin;

    UPROPERTY(BlueprintAssignable)
    FFIEAMontageNotifyTaskDelegate OnNotifyEnd;

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "UFIEA_PlayMontageAndWaitForEvent",
        HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
    static UFIEA_PlayMontageAndWaitForEvent* FIEACreatePlayMontageAndWaitForEvent(UGameplayAbility* OwningAbility,
        FName NewTaskInstanceName, UAnimMontage* NewMontageToPlay, float NewRate = 1.f, FName NewStartSection = NAME_None, bool bNewStopWhenAbilityEnds = true, float NewAnimRootMotionTranslationScale = 1.f, float NewStartTimeSeconds = 0.f, bool bNewAllowInterruptAfterBlendOut = false);

protected:

    virtual void Activate() override;

    UFUNCTION()
    void OnPlayFIEAMontageNotifyBegin(FName TheNotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

    UFUNCTION()
    void OnPlayFIEAMontageNotifyEnd(FName TheNotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
};
