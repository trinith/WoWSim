#include "MeleeAttackCalculator.h"

#include <WoWSimDebugLogging.h>

namespace
{
    struct CalculationStep
    {
        sim::MeleeHitResult result;
        std::function<float(const sim::Character&, const sim::Character&)> func;
    };

    inline static const std::array calculations
    {
        CalculationStep{ sim::MeleeHitResult::Miss,     sim::MeleeAttackCalculator::CalculateMissChance },
        CalculationStep{ sim::MeleeHitResult::Dodge,    sim::MeleeAttackCalculator::CalculateDodgeChance },
        CalculationStep{ sim::MeleeHitResult::Parry,    sim::MeleeAttackCalculator::CalculateParryChance },
        CalculationStep{ sim::MeleeHitResult::Glancing, sim::MeleeAttackCalculator::CalculateGlancingChance },
        CalculationStep{ sim::MeleeHitResult::Block,    sim::MeleeAttackCalculator::CalculateBlockChance },
        CalculationStep{ sim::MeleeHitResult::Crit,     sim::MeleeAttackCalculator::CalculateCritChance },
        CalculationStep{ sim::MeleeHitResult::Crushing, sim::MeleeAttackCalculator::CalculateCrushingBlowChance }
    };

    int32_t CalculateMaxSkill(const sim::Character& character)
    {
        return character.GetCharacterIdData().level * 5;
    }
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

    float MeleeAttackCalculator::CalculateMissChance(const sim::Character& attacker, const sim::Character& target)
    {
        const sim::Attributes& attackerAttributes = attacker.GetAttributes();
        const sim::Attributes& targetAttributes = target.GetAttributes();

        int32_t attackerWeaponSkill = attackerAttributes.combatAttributes.weaponSkill;
        int32_t targetDefense = targetAttributes.defenseAttributes.defense;
        int32_t skillDiff = targetDefense - attackerWeaponSkill;

        // GT_TODO: Update for dual wield...
        float missChance =
            (skillDiff <= 10)
            ? 0.05f + skillDiff * 0.001f
            : 0.07f + skillDiff * 0.004f;

        missChance = std::clamp(missChance, 0.f, 1.f);

        return missChance;
    }

    float MeleeAttackCalculator::CalculateDodgeChance(const sim::Character& attacker, const sim::Character& target)
    {
        const sim::Attributes& attackerAttributes = attacker.GetAttributes();
        const sim::Attributes& targetAttributes = target.GetAttributes();
        
        float dodge = targetAttributes.defenseAttributes.dodge;
        dodge += (targetAttributes.defenseAttributes.defense - attackerAttributes.combatAttributes.weaponSkill) * 0.0004f;

        return dodge;
    }

    float MeleeAttackCalculator::CalculateParryChance(const sim::Character& attacker, const sim::Character& target)
    {
        const sim::Attributes& attackerAttributes = attacker.GetAttributes();
        const sim::Attributes& targetAttributes = target.GetAttributes();

        float parry = targetAttributes.defenseAttributes.parry;
        parry += (targetAttributes.defenseAttributes.defense - attackerAttributes.combatAttributes.weaponSkill) * 0.0004f;

        return parry;
    }

    float MeleeAttackCalculator::CalculateGlancingChance(const sim::Character& attacker, const sim::Character& target)
    {
        // GT_TODO: Implement glancing blow chance calculation.
        return 0.0f;
    }

    float MeleeAttackCalculator::CalculateBlockChance(const sim::Character& attacker, const sim::Character& target)
    {
        const sim::Attributes& targetAttributes = target.GetAttributes();
        return targetAttributes.defenseAttributes.block;
    }

    float MeleeAttackCalculator::CalculateCritChance(const sim::Character& attacker, const sim::Character& target)
    {
        const sim::Attributes& attackerAttributes = attacker.GetAttributes();
        const sim::Attributes& targetAttributes = target.GetAttributes();

        float crit = attackerAttributes.combatAttributes.crit;

        // GT_TODO: This is wrong. 
        // Should use skillDiff = attackerWeaponSkill - targetDefense. Will need to implement weapon skills to achieve this.
        // Apparently this is a bit more subtle than that, see:
        //      https://www.reddit.com/r/classicwow/comments/df6fr5/new_crit_chance_calculation_weapon_skillagility/
        int32_t targetMaxDefense = CalculateMaxSkill(target);
        int32_t skillDiff = targetAttributes.defenseAttributes.defense - targetMaxDefense;
        crit -= skillDiff * 0.0004f;

        return crit;
    }

    float MeleeAttackCalculator::CalculateCrushingBlowChance(const sim::Character& attacker, const sim::Character& target)
    {
        // GT_TODO: Implement crushing blow chance calculation.
        return 0.0f;
    }

}