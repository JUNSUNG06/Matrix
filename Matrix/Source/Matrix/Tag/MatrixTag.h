#pragma once

#include "GameplayTagContainer.h"

#define ABILITY_CHARACTER_DAMAGED FGameplayTag::RequestGameplayTag(FName("Ability.Character.Damaged"))
#define ABILITY_CHARACTER_PARRIED FGameplayTag::RequestGameplayTag(FName("Ability.Character.Parried"))
#define ABILITY_CHARACTER_STARTSTUN FGameplayTag::RequestGameplayTag(FName("Ability.Character.StartStun"))
#define ABILITY_CHARACTER_DIE FGameplayTag::RequestGameplayTag(FName("Ability.Character.Die"))