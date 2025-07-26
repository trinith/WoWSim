#include <Actions/AutoSwingAction.h>
#include <Actions/SimulationEndAction.h>

#include <Simulation/Simulation.h>
#include <Simulation/Character/CharacterManager.h>

#include <Util/Debug/CharacerDebugOutput.h>

#include <WoWSimDebugLogging.h>

int main(void)
{
    sim::Simulation simulation{};
	sim::CharacterManager& characterManager = simulation.GetCharacterManager();

    uint64_t smellyId = *characterManager.CreateCharacter<sim::PlayerCharacter>(
        sim::CharacterIdentifierData{ "Smellybeard", 25 },
        sim::PlayerIdentifierData{ sim::RaceId::Dwarf, sim::ClassId::Paladin }
    );
	sim::PlayerCharacter& smellyPlayer = *characterManager.TryGet<sim::PlayerCharacter>(smellyId);

    uint64_t ammyId = *characterManager.CreateCharacter<sim::PlayerCharacter>(
        sim::CharacterIdentifierData{ "Amarict", 25 },
        sim::PlayerIdentifierData{ sim::RaceId::Human, sim::ClassId::Paladin }
    );

    uint64_t hoggerId = *characterManager.CreateCharacter<sim::MobCharacter>(
        sim::CharacterIdentifierData{ "Hogger", 11 },
        sim::PrimaryAttributes{ 25, 25, 25, 25, 25}
	);

    smellyPlayer.GetTargetManager().SetTarget(ammyId);

    util::OutputCharacter<sim::PlayerCharacter>(characterManager, smellyId);
    util::OutputCharacter<sim::PlayerCharacter>(characterManager, ammyId);
    util::OutputCharacter<sim::MobCharacter>(characterManager, hoggerId);
    std::cout << std::endl;

    simulation.QueueAction<actions::SimulationEndAction>(20000);
    simulation.QueueAction<actions::AutoSwingAction>(0, smellyId);

    while (simulation.IsRunning())
        simulation.Tick();

    return 0;
}