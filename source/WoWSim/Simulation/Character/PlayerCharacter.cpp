#include "PlayerCharacter.h"

#include <Data/ClassAttributesPerLevel.h>

namespace sim
{

    PlayerCharacter::PlayerCharacter(uint64_t id, CharacterIdentifierData charIdData, PlayerIdentifierData playerIdData)
        : _playerIdData{ playerIdData }
        , Character{ id, std::move(charIdData), {} }
    {
        PrimaryAttributes& primaryAttributes = _attributes.primaryAttributes;
        primaryAttributes += data::RaceAttributeModifiers.at(playerIdData.raceId);
        primaryAttributes += data::ClassAttributesPerLevel.at(playerIdData.classId)[_charIdData.level - 1];
    }

}