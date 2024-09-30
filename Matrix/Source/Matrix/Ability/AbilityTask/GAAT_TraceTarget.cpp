// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityTask/GAAT_TraceTarget.h"

#include "AbilitySystemComponent.h"

#include "../TargetActor/GATA_SphereTrace.h"
#include "../../Interface/Interact.h"

UGAAT_TraceTarget::UGAAT_TraceTarget()
{

}

UGAAT_TraceTarget* UGAAT_TraceTarget::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<class AGATA_SphereTrace> TargetActorClass)
{
    UGAAT_TraceTarget* NewTask = NewAbilityTask<UGAAT_TraceTarget>(OwningAbility);
    NewTask->TargetActorClass = TargetActorClass;

    return NewTask;
}

void UGAAT_TraceTarget::Activate()
{
    Super::Activate();

    SpawnAndInitializeTargetActor();
    FinalizeTargetActor();

    SetWaitingOnAvatar();
}

void UGAAT_TraceTarget::OnDestroy(bool AbilityEnded)
{
    if (SpawnedTargetActor)
    {
        SpawnedTargetActor->Destroy();
    }

    Super::OnDestroy(AbilityEnded);
}

void UGAAT_TraceTarget::SpawnAndInitializeTargetActor()
{
    SpawnedTargetActor = Cast<AGATA_SphereTrace>(Ability->GetWorld()->
        SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetActorClass, FTransform::Identity,
            nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
    if (SpawnedTargetActor)
    {
        SpawnedTargetActor->SetTraceData(TraceRange, TraceRadius);
        SpawnedTargetActor->SetShowDebug(true);
        SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this,
            &UGAAT_TraceTarget::OnTargetDataReadyCallback);
    }
}

void UGAAT_TraceTarget::FinalizeTargetActor()
{
    UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
    if (ASC)
    {
        FTransform Transform = ASC->GetAvatarActor()->GetTransform();
        SpawnedTargetActor->FinishSpawning(Transform);

        ASC->SpawnedTargetActors.Push(SpawnedTargetActor);
        SpawnedTargetActor->StartTargeting(Ability);
        SpawnedTargetActor->ConfirmTargeting();
    }
}

void UGAAT_TraceTarget::SetTraceData(float Range, float Radius)
{
    TraceRange = Range;
    TraceRadius = Radius;
}

void UGAAT_TraceTarget::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnComplete.Broadcast(DataHandle);
    }

    EndTask();
}
