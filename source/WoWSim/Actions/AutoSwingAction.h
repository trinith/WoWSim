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
			ActionData data = PrepareActionData(simulation);
            if (!data.IsValid())
                return;

            const sim::SimulationConsoleLog& log = simulation.GetConsoleLog();
            const sim::Character& character = *data.character;
            const sim::Character& target = *data.target;

			log.WriteLine("", character.GetCharacterIdData().name, " swings at ", target.GetCharacterIdData().name, ".");

            constexpr sim::Simulation::TimeType swingTime = 3800;
            simulation.QueueAction<AutoSwingAction>(swingTime, _characterId);
        }

    private:
        struct ActionData
        {
            OptionalRef<const sim::Character> character;
            OptionalRef<const sim::Character> target;

            bool IsValid() const { return character && target; }
        };

        ActionData PrepareActionData(const sim::Simulation& simulation) const
        {
            ActionData data{};

            const sim::SimulationConsoleLog& log = simulation.GetConsoleLog();

            const sim::CharacterManager& characterManager = simulation.GetCharacterManager();
            data.character = characterManager.TryGet<sim::Character>(_characterId);
            if (!data.character)
            {
                log.WriteLine("Character with id, ", _characterId, ", no longer exists. Cancelling this AutoSwingAction.");
                return data;
            }

            std::optional<uint64_t> targetId = data.character->get().GetTargetManager().GetTarget();

            if (!targetId)
            {
                log.WriteLine("Character with id, ", _characterId, ", has no target. Cancelling this AutoSwingAction.");
                return data;
            }

            data.target = characterManager.TryGet<sim::Character>(*targetId);
            if (!data.target)
            {
                log.WriteLine("Target with id, ", *targetId, ", no longer exists. Cancelling this AutoSwingAction.");
                return data;
            }

            return data;
        }

        uint64_t _characterId{};
    };

}