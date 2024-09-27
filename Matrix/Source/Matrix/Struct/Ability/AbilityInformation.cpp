#include "AbilityInformation.h"

bool FAbilityActivationInfo::operator==(FAbilityActivationInfo& Left)
{
	return Ability == Left.Ability && InputAction == Left.InputAction && Tag == Left.Tag;
}