#pragma once

#include <Simulation/IAction.h>
#include <Simulation/TemporalQueue.h>
#include <Simulation/Character/CharacterManager.h>

namespace sim
{

	class Simulation
	{
	public:
		using TimeType = uint32_t;

	public:
		bool IsRunning() const { return _isRunning; }
		TimeType CurrentTime() const { return _currentTime; }
		const CharacterManager& GetCharacterManager() const { return _characterManager; }
		CharacterManager& GetCharacterManager() { return _characterManager; }

		template <typename TActionType, typename... TArgs>
		void QueueAction(TimeType t, TArgs&&... args)
		{
			_actionQueue.Enqueue<TActionType>(t, args...);
		}

		void Tick()
		{
			if (!_isRunning)
				return;

			if (_actionQueue.IsEmpty())
				return;

			_currentTime += _actionQueue.NextTime();
			std::unique_ptr<IAction> action = _actionQueue.Pop();
			action->Execute(*this);

			std::cout << "Q: " << _actionQueue.ToString() << std::endl;

			_isRunning = !_actionQueue.IsEmpty();
		}

		void Stop()
		{
			_actionQueue.Clear();
			_isRunning = false;
		}

	private:
		CharacterManager _characterManager;
		TemporalQueue<TimeType, IAction> _actionQueue;
		TimeType _currentTime = 0;
		bool _isRunning = true;
	};

}