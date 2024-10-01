#include "AbilityInformation.h"
#include "Abilities/GameplayAbility.h"

bool FAbilityActivationInfo::operator==(FAbilityActivationInfo& Other)
{
	return Ability == Other.Ability && InputAction == Other.InputAction && Tag == Other.Tag;
}

bool FAbilityActivationInfo::operator==(const FAbilityActivationInfo& Other) const
{
	return Ability == Other.Ability && InputAction == Other.InputAction && Tag == Other.Tag;
}