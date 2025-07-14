#pragma once

#include <optional>
#include <vector>

namespace sim
{

    class TargetManager
    {
    public:
		using TargetType = std::optional<uint64_t>;

    public:
        const TargetType GetTarget() const { return _target; }
        
        void SetTarget(uint64_t targetId)
        {
            _target.emplace(targetId);
        }

        void ClearTarget()
        {
            _target.reset();
		}

    private:
        TargetType _target{};
    };

}