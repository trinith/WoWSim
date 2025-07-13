#pragma once

#include <Simulation/Character/Character.h>

namespace sim
{

	class MobCharacter : public Character
	{
	public:
		MobCharacter(uint64_t id, CharacterIdentifierData charIdData, PrimaryAttributes baseAttributes)
			: Character{ id, std::move(charIdData), std::move(baseAttributes) }
		{
		}

		CharacterType GetCharacterType() const override { return CharacterType::Mob; }
	};

}