#pragma once

#include <Actions/ActionBase.h>
#include <Simulation/Simulation.h>

namespace actions
{

    class AutoSwingAction : public actions::ActionBase
    {
    public:
        AutoSwingAction(std::uint64_t characterId)
			: ActionBase()
            , _characterId{ characterId }
        {
        }

        std::string ToString() const override
        {
            return "{AutoSwingAction}";
        }

    protected:
        void OnExecute(sim::Simulation& simulation) override
        {
			const sim::SimulationConsoleLog& log = simulation.GetConsoleLog();

            const sim::CharacterManager& characterManager = simulation.GetCharacterManager();
			OptionalRef<const sim::Character> characterResult = characterManager.TryGet<sim::Character>(_characterId);
            if (!characterResult)
            {
                log.WriteLine("Character with id, ", _characterId, ", no longer exists. Cancelling this AutoSwingAction.");
                return;
			}

			const sim::Character& character = characterResult->get();
			std::optional<uint64_t> targetId = character.GetTargetManager().GetTarget();

            if (!targetId)
            {
				log.WriteLine("Character with id, ", _characterId, ", has no target. Cancelling this AutoSwingAction.");
                return;
            }

			OptionalRef<const sim::Character> targetResult = characterManager.TryGet<sim::Character>(*targetId);
            if (!targetResult)
            {
                log.WriteLine("Target with id, ", *targetId, ", no longer exists. Cancelling this AutoSwingAction.");
                return;
			}

			const sim::Character& target = targetResult->get();

			log.WriteLine("", character.GetCharacterIdData().name, " swings at ", target.GetCharacterIdData().name, ".");

            constexpr sim::Simulation::TimeType swingTime = 3800;
            simulation.QueueAction<AutoSwingAction>(swingTime, _characterId);
        }

    private:
        uint64_t _characterId{};
    };

}