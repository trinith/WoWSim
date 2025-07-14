#pragma once

#include <Simulation/Character/CharacterManager.h>

#include <WoWSimDebugLogging.h>
#include <magic_enum/magic_enum.hpp>

namespace debugutil
{
    void OutputTargetDetail(const sim::CharacterManager& characterManager, sim::TargetManager::TargetType target)
    {
        if (target)
        {
            if (OptionalRef<const sim::Character> targetCharacter = characterManager.TryGet(*target))
            {
				const sim::Character& targetChararacter = *targetCharacter;
                LOG_WRITELINE("* Target: ", targetChararacter.GetCharacterIdData().name, " (", *target, ")");
                return;
            }
        }

        LOG_WRITELINE("* Target: NONE");
    }

    template<typename TCharacter>
    void OutputCharacterDetail(const TCharacter& character) {}

    template <>
    void OutputCharacterDetail(const sim::PlayerCharacter& character)
    {
        const sim::PlayerIdentifierData data = character.GetPlayerIdData();
        LOG_WRITELINE("* Race: ", magic_enum::enum_name(data.raceId));
        LOG_WRITELINE("* Class: ", magic_enum::enum_name(data.classId));
    }

    template<typename TCharacter>
		requires std::is_base_of_v<sim::Character, TCharacter>
    void OutputCharacter(const sim::CharacterManager& characterManager, uint64_t characterId)
    {
        auto result = characterManager.TryGet<TCharacter>(characterId);
        if (!result)
        {
            LOG_WRITELINE("Character with ID ", characterId, " not found.");
            return;
        }

        const TCharacter& character = *result;

        const sim::CharacterIdentifierData& charData = character.GetCharacterIdData();

        LOG_WRITELINE(charData.name);
        LOG_INDENT(detailScope);
        LOG_WRITELINE("* Id: ", character.GetId());
        LOG_WRITELINE("* Level: ", charData.level);
        OutputCharacterDetail<TCharacter>(character);
        LOG_WRITELINE("* Primary Attributes: ", character.GetAttributes().primaryAttributes);
		OutputTargetDetail(characterManager, character.GetTargetManager().GetTarget());
    }

}