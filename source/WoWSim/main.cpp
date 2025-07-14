#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_map>
#include <variant>

#include <Actions/AutoSwingAction.h>
#include <Actions/SimulationEndAction.h>

#include <Simulation/Simulation.h>
#include <Simulation/Character/CharacterManager.h>

#include <Util/Debug/CharacerDebugOutput.h>

#include <WoWSimDebugLogging.h>
#include <magic_enum/magic_enum.hpp>

int main(void)
{
    sim::Simulation simulation{};
	sim::CharacterManager& characterManager = simulation.GetCharacterManager();

    uint64_t smellyId = characterManager.CreatePlayerCharacter(
        { "Smellybeard", 25 },
        { sim::RaceId::Dwarf, sim::ClassId::Paladin }
    );
	sim::PlayerCharacter& smellyPlayer = *characterManager.TryGet<sim::PlayerCharacter>(smellyId);

    uint64_t ammyId = characterManager.CreatePlayerCharacter(
        { "Amarict", 25 },
        { sim::RaceId::Human, sim::ClassId::Paladin }
    );

    uint64_t hoggerId = characterManager.CreateMobCharacter(
        { "Hogger", 11 },
        { 25, 25, 25, 25, 25}
	);

    smellyPlayer.GetTargetManager().SetTarget(ammyId);

    debugutil::OutputCharacter<sim::PlayerCharacter>(characterManager, smellyId);
    debugutil::OutputCharacter<sim::PlayerCharacter>(characterManager, ammyId);
    debugutil::OutputCharacter<sim::MobCharacter>(characterManager, hoggerId);
    std::cout << std::endl;

    simulation.QueueAction<actions::SimulationEndAction>(20000);
    simulation.QueueAction<actions::AutoSwingAction>(0);

    while (simulation.IsRunning())
        simulation.Tick();

    return 0;
}