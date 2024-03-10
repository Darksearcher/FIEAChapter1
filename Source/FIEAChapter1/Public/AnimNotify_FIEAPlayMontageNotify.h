// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "GameplayTagsManager.h"
#include "AnimNotify_FIEAPlayMontageNotify.generated.h"

/**
 * 
 */
UCLASS()
class FIEACHAPTER1_API UAnimNotify_FIEAPlayMontageNotify : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()

	virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;

	virtual FString GetNotifyName_Implementation() const override;

protected:
	// Name of notify that is passed to the PlayMontage K2Node.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Notify", meta = (Categories = "Montage.Notify"))
	FGameplayTag GameplayTagNotify;
};


UCLASS()
class  FIEACHAPTER1_API UAnimNotify_FIEAPlayMontageNotifyWindow : public UAnimNotify_PlayMontageNotifyWindow
{
	GENERATED_BODY()

	virtual void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) override;

	virtual void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) override;

	virtual FString GetNotifyName_Implementation() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Notify", meta = (Categories = "Montage.Notify"))
	FGameplayTag GameplayTagNotify;
};