#pragma once

#include <Data/BasicCharacterData.h>
#include <Simulation/Attributes.h>
#include <Simulation/TargetManager.h>

#include <algorithm>
#include <string>
#include <vector>

namespace sim
{

	enum class CharacterType : uint8_t
    {
        Mob = 0,
        Player
    };

    struct CharacterIdentifierData
    {
        std::string name;
        uint32_t level;
    };

    class Character
    {
    public:
        Character(uint64_t id, CharacterIdentifierData idData, Attributes attributes)
            : _id{ id }
            , _charIdData{ std::move(idData) }
            , _attributes{ std::move(attributes) }
        {
            _charIdData.level = std::clamp(_charIdData.level, 1u, data::MaxLevel);

            _attributes.combatAttributes.weaponSkill = _charIdData.level * 5;
            _attributes.defenseAttributes.defense = _charIdData.level * 5;
        }

		virtual CharacterType GetCharacterType() const = 0;

        const uint64_t GetId() const { return _id; }
        const CharacterIdentifierData& GetCharacterIdData() const { return _charIdData; }
        
        const Attributes& GetAttributes() const { return _attributes; }
		Attributes& GetAttributes() { return _attributes; }

		const TargetManager& GetTargetManager() const { return _targetManager; }
        TargetManager& GetTargetManager() { return _targetManager; }

    protected:
        uint64_t _id;
        CharacterIdentifierData _charIdData;
        Attributes _attributes;

        TargetManager _targetManager{};
    };

}