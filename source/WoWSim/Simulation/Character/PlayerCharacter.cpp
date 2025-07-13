#include "PlayerCharacter.h"

#include <Data/ClassAttributesPerLevel.h>

namespace sim
{

    PlayerCharacter::PlayerCharacter(uint64_t id, CharacterIdentifierData charIdData, PlayerIdentifierData playerIdData)
        : _playerIdData{ playerIdData }
        , Character{ id, std::move(charIdData), {} }
    {
        _baseAttributes += data::RaceAttributeModifiers.at(playerIdData.raceId);
        _baseAttributes += data::ClassAttributesPerLevel.at(playerIdData.classId)[_charIdData.level - 1];
    }

}