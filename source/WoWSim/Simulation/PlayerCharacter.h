#pragma once

#include <Simulation/Character.h>

namespace sim
{

    struct PlayerIdentifierData
    {
        RaceId raceId;
        ClassId classId;
    };

    class PlayerCharacter : public Character
    {
    public:
        PlayerCharacter(uint64_t id, CharacterIdentifierData charIdData, PlayerIdentifierData playerIdData);

        const PlayerIdentifierData& GetPlayerIdData() const { return _playerIdData; }
    protected:
        PlayerIdentifierData _playerIdData;
    };

}