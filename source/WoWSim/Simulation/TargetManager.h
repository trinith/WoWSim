#pragma once

#include <vector>

namespace sim
{

	using TargetVector = std::vector<uint64_t>;

    class TargetManager
    {
    public:
		const bool IsEmpty() const { return _targets.empty(); }
        const TargetVector& GetTargets() const { return _targets; }

        void AddTarget(uint64_t targetId)
        {
            if (std::find(_targets.begin(), _targets.end(), targetId) == _targets.end())
                _targets.push_back(targetId);
        }

        void RemoveTarget(uint64_t targetId)
        {
            auto it = std::remove(_targets.begin(), _targets.end(), targetId);
            if (it != _targets.end())
                _targets.erase(it, _targets.end());
        }

        void ClearTargets()
        {
            _targets.clear();
        }

    private:
        TargetVector _targets;
    };

}