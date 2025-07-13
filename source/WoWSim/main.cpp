#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_map>
#include <variant>

#include <Simulation/Simulation.h>
#include <Simulation/CharacterManager.h>

#include <Actions/AutoSwingAction.h>
#include <Actions/SimulationEndAction.h>

#include <magic_enum/magic_enum.hpp>

int main(void)
{
    sim::Simulation simulation{};

    uint64_t playerId = simulation.GetCharacterManager().CreatePlayerCharacter(
        { "Smellybeard", 25 },
        { sim::RaceId::Dwarf, sim::ClassId::Paladin }
    );
	const sim::PlayerCharacter& player = *simulation.GetCharacterManager().TryGet<sim::PlayerCharacter>(playerId);

    std::cout << player.GetCharacterIdData().name << " is a level " << player.GetCharacterIdData().level
        << " " << magic_enum::enum_name(player.GetPlayerIdData().raceId) << " " << magic_enum::enum_name(player.GetPlayerIdData().classId)
        << " with basic attributes: " << player.GetBaseAttributes() << std::endl << std::endl;
  
    simulation.QueueAction<actions::SimulationEndAction>(20000);
    simulation.QueueAction<actions::AutoSwingAction>(0);

    while (simulation.IsRunning())
        simulation.Tick();

    return 0;
}