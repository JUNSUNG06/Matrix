#include "AbilityInformation.h"
#include "Abilities/GameplayAbility.h"

bool FAbilityActivationInfo::operator==(FAbilityActivationInfo& Right)
{
	return Ability == Right.Ability && InputAction == Right.InputAction && Tag == Right.Tag;
}