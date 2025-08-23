#pragma once

#include <Actions/ActionBase.h>

#include <Simulation/DamageType.h>
#include <Simulation/Simulation.h>
#include <Simulation/Calculation/MeleeAttackCalculator.h>

#include <Util/Random.h>

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

            const sim::CombatLog& log = simulation.GetCombatLog();
            const sim::Character& character = *data.character;
            const sim::Character& target = *data.target;

            float roll = util::Random::Next(0, 10000) / 100.f;
            sim::MeleeHitResult hitResult = sim::MeleeAttackCalculator::DetermineHitResult(roll, character, target);

            if (hitResult <= sim::MeleeHitResult::Parry)
            {
                log.LogEvent(
                    sim::EventType::Miss,
                    sim::MissEventData{
                        simulation.CurrentTime(),
                        character.GetId(),
                        target.GetId(),
                        static_cast<sim::MissType>(hitResult)
                    }
                );
            }
            else
            {
                float damage = 123.456f; // GT_TODO: Calculate damage based on MeleeHitResult.
                if (hitResult == sim::MeleeHitResult::Crit)
                    damage *= 2.f;

                log.LogEvent(
                    sim::EventType::Damage,
                    sim::DamageEventData{
                        simulation.CurrentTime(),
                        character.GetId(),
                        target.GetId(),
                        damage,
                        sim::DamageType::Physical,
                        hitResult == sim::MeleeHitResult::Crit
                    }
                );
            }

            constexpr sim::Simulation::TimeType swingTime = 3800; // GT_TODO: Get swing timer from character.
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