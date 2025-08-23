#include "MeleeAttackCalculator.h"

namespace
{
    struct CalculationStep
    {
        sim::MeleeHitResult result;
        std::function<float(const sim::Character&, const sim::Character&)> func;
    };

    static float CalculateMissChance(const sim::Character& attacker, const sim::Character& target);
    static float CalculateDodgeChance(const sim::Character& attacker, const sim::Character& target);
    static float CalculateParryChance(const sim::Character& attacker, const sim::Character& target);
    static float CalculateGlancingChance(const sim::Character& attacker, const sim::Character& target);
    static float CalculateBlockChance(const sim::Character& attacker, const sim::Character& target);
    static float CalculateCritChance(const sim::Character& attacker, const sim::Character& target);
    static float CalculateCrushingBlowChance(const sim::Character& attacker, const sim::Character& target);

    inline static const std::array calculations
    {
        CalculationStep{ sim::MeleeHitResult::Miss, CalculateMissChance },
        CalculationStep{ sim::MeleeHitResult::Dodge, CalculateDodgeChance },
        CalculationStep{ sim::MeleeHitResult::Parry, CalculateParryChance },
        CalculationStep{ sim::MeleeHitResult::Glancing, CalculateGlancingChance },
        CalculationStep{ sim::MeleeHitResult::Block, CalculateBlockChance },
        CalculationStep{ sim::MeleeHitResult::Crit, CalculateCritChance },
        CalculationStep{ sim::MeleeHitResult::Crushing, CalculateCrushingBlowChance }
    };
}

namespace sim
{

    /*static*/
    MeleeHitResult MeleeAttackCalculator::DetermineHitResult(float rollBase, const sim::Character& attacker, const sim::Character& target)
    {
        const int32_t rollPrecision = 1000;
        const int32_t rollMax = 100;
        const int32_t adjustedMax = rollMax * rollPrecision;

        rollBase = std::clamp(rollBase, 0.f, 100.f);

        int32_t roll = std::clamp<int32_t>(static_cast<int32_t>((rollMax - rollBase) * rollPrecision), 0, adjustedMax);
        int32_t check = adjustedMax;

        const sim::Attributes& attackerAttributes = attacker.GetAttributes();
        const sim::Attributes& targetAttributes = target.GetAttributes();

        for (auto&& calculation : calculations)
        {
            float chance = calculation.func(attacker, target);
            check -= static_cast<int32_t>(chance * adjustedMax);
            if (roll >= check)
                return calculation.result;
        }
        return MeleeHitResult::Hit;
    }

}

namespace
{
    /*static*/
    float CalculateMissChance(const sim::Character& attacker, const sim::Character& target)
    {
        const sim::Attributes& attackerAttributes = attacker.GetAttributes();
        const sim::Attributes& targetAttributes = target.GetAttributes();

        int32_t attackerWeaponSkill = attacker.GetCharacterIdData().level * 5; // GT_TODO: Add weapon skill to attributes and get from there.
        int32_t targetDefense = target.GetCharacterIdData().level * 5 + targetAttributes.defenseAttributes.defense; // GT_TODO: Add defense to attributes and get from there.
        int32_t skillDiff = targetDefense - attackerWeaponSkill;

        // GT_TODO: Update for dual wield...
        float missChance =
            (skillDiff <= 10)
            ? 0.05f + skillDiff * 0.1f
            : 0.07f + skillDiff * 0.4f;
        missChance = std::clamp(missChance, 0.f, 1.f);

        return missChance;
    }

    /*static*/
    float CalculateDodgeChance(const sim::Character& attacker, const sim::Character& target)
    {
        const sim::Attributes& targetAttributes = target.GetAttributes();
        return targetAttributes.defenseAttributes.dodge;
    }

    /*static*/
    float CalculateParryChance(const sim::Character& attacker, const sim::Character& target)
    {
        const sim::Attributes& targetAttributes = target.GetAttributes();
        return targetAttributes.defenseAttributes.parry;
    }

    /*static*/
    float CalculateGlancingChance(const sim::Character& attacker, const sim::Character& target)
    {
        // GT_TODO: Implement glancing blow chance calculation.
        return 0.0f;
    }

    /*static*/
    float CalculateBlockChance(const sim::Character& attacker, const sim::Character& target)
    {
        const sim::Attributes& targetAttributes = target.GetAttributes();
        return targetAttributes.defenseAttributes.block;
    }

    /*static*/
    float CalculateCritChance(const sim::Character& attacker, const sim::Character& target)
    {
        // GT_TODO: I'm pretty sure defense modifies crit chance somehow... look into that.
        const sim::Attributes& attackerAttributes = attacker.GetAttributes();
        return attackerAttributes.combatAttributes.crit;
    }

    /*static*/
    float CalculateCrushingBlowChance(const sim::Character& attacker, const sim::Character& target)
    {
        // GT_TODO: Implement crushing blow chance calculation.
        return 0.0f;
    }

}