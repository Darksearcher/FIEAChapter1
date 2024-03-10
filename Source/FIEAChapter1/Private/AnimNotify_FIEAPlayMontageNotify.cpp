// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_FIEAPlayMontageNotify.h"

void UAnimNotify_FIEAPlayMontageNotify::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
    NotifyName = FName(GameplayTagNotify.ToString());
    Super::BranchingPointNotify(BranchingPointPayload);
}

FString UAnimNotify_FIEAPlayMontageNotify::GetNotifyName_Implementation() const
{
    return GameplayTagNotify.ToString();
}

void UAnimNotify_FIEAPlayMontageNotifyWindow::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
    NotifyName = FName(GameplayTagNotify.ToString());
	Super::BranchingPointNotifyBegin(BranchingPointPayload);
}

void UAnimNotify_FIEAPlayMontageNotifyWindow::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
    NotifyName = FName(GameplayTagNotify.ToString());
    Super::BranchingPointNotifyEnd(BranchingPointPayload);
}

FString UAnimNotify_FIEAPlayMontageNotifyWindow::GetNotifyName_Implementation() const
{
    return GameplayTagNotify.ToString();
}