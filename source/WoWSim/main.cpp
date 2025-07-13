#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_map>
#include <variant>

#include <Actions/AutoSwingAction.h>
#include <Actions/SimulationEndAction.h>
#include <Simulation/Simulation.h>
#include <Simulation/CharacterManager.h>

#include <WoWSimDebugLogging.h>
#include <magic_enum/magic_enum.hpp>

void DebugOutput(const sim::CharacterManager& characterManager, uint64_t characterId)
{
    auto result = characterManager.TryGet<sim::PlayerCharacter>(characterId);
    if (!result)
    {
        LOG_WRITELINE("Character with ID ", characterId, " not found.");
        return;
    }

	const sim::PlayerCharacter& character = *result;

    const sim::CharacterIdentifierData& charData = character.GetCharacterIdData();
	const sim::PlayerIdentifierData& playerData = character.GetPlayerIdData();

    LOG_WRITELINE(charData.name);
    LOG_INDENT(detailScope);
	LOG_WRITELINE("* Id: ", character.GetId());
	LOG_WRITELINE("* Level: ", charData.level, " ", magic_enum::enum_name(playerData.raceId), " ", magic_enum::enum_name(playerData.classId));
	LOG_WRITELINE("* Base Attributes: ", character.GetBaseAttributes());

    LOG_WRITELINE("* Targets:");
	const sim::TargetManager& targetManager = character.GetTargetManager();
    if (!targetManager.IsEmpty())
    {
        LOG_INDENT(targetScope);
        for (auto&& targetId : targetManager.GetTargets())
        {
            auto targetResult = characterManager.TryGet<sim::PlayerCharacter>(targetId);
            if (targetResult)
				LOG_WRITELINE(targetResult->get().GetCharacterIdData().name, " (id=", targetId, ")");
        }
    }
    else
    {
        LOG_INDENT(targetScope);
        LOG_WRITELINE("NONE");
    }
}

int main(void)
{
    sim::Simulation simulation{};

    uint64_t playerId = simulation.GetCharacterManager().CreatePlayerCharacter(
        { "Smellybeard", 25 },
        { sim::RaceId::Dwarf, sim::ClassId::Paladin }
    );
	sim::PlayerCharacter& player = *simulation.GetCharacterManager().TryGet<sim::PlayerCharacter>(playerId);

    uint64_t mobId = simulation.GetCharacterManager().CreatePlayerCharacter(
        { "Amarict", 25 },
        { sim::RaceId::Human, sim::ClassId::Paladin }
    );

    player.GetTargetManager().AddTarget(mobId);

    DebugOutput(simulation.GetCharacterManager(), playerId);
	DebugOutput(simulation.GetCharacterManager(), mobId);
    std::cout << std::endl;

      simulation.QueueAction<actions::SimulationEndAction>(20000);
    simulation.QueueAction<actions::AutoSwingAction>(0);

    while (simulation.IsRunning())
        simulation.Tick();

    return 0;
}