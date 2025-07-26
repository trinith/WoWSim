#pragma once

#include <Actions/ActionBase.h>
#include <Simulation/Simulation.h>

#include <WoWSimDebugLogging.h>

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
            const sim::CharacterManager& characterManager = simulation.GetCharacterManager();
			OptionalRef<const sim::Character> characterResult = characterManager.TryGet<sim::Character>(_characterId);
            if (!characterResult)
            {
                LOG_WRITELINE("[", simulation.CurrentTime(), "] Character with id, ", _characterId, ", no longer exists. Cancelling this AutoSwingAction.");
                return;
			}

			const sim::Character& character = characterResult->get();
			std::optional<uint64_t> targetId = character.GetTargetManager().GetTarget();

            if (!targetId)
            {
				LOG_WRITELINE("[", simulation.CurrentTime(), "] Character with id, ", _characterId, ", has no target. Cancelling this AutoSwingAction.");
                return;
            }

			OptionalRef<const sim::Character> targetResult = characterManager.TryGet<sim::Character>(*targetId);
            if (!targetResult)
            {
                LOG_WRITELINE("[", simulation.CurrentTime(), "] Target with id, ", *targetId, ", no longer exists. Cancelling this AutoSwingAction.");
                return;
			}

			const sim::Character& target = targetResult->get();

			LOG_WRITELINE("[", simulation.CurrentTime(), "] ", character.GetCharacterIdData().name, " swings at ", target.GetCharacterIdData().name, ".");

            constexpr sim::Simulation::TimeType swingTime = 3800;
            simulation.QueueAction<AutoSwingAction>(swingTime, _characterId);
        }

    private:
        uint64_t _characterId{};
    };

}