#pragma once

#include <Simulation/IAction.h>
#include <Simulation/SimulationConsoleLog.h>
#include <Simulation/TemporalQueue.h>

#include <Simulation/Character/CharacterManager.h>
#include <Simulation/CombatLog/ConsoleLogEventWriter.h>

namespace sim
{
	class ConsoleLogEventWriter;

	class Simulation
	{
	public:
		using TimeType = uint32_t;

	public:
		Simulation()
		{
			_combatLog.CombatEventLogged += [this](const CombatLog& log, const CombatLog::EventInfo& eventInfo)
			{
				ConsoleLogEventWriter::Write(*this, eventInfo);
			};
		}

		const SimulationConsoleLog& GetConsoleLog() const { return _consoleLog; }
		const CombatLog& GetCombatLog() const { return _combatLog; }
		CombatLog& GetCombatLog() { return _combatLog; }
		const CharacterManager& GetCharacterManager() const { return _characterManager; }
		CharacterManager& GetCharacterManager() { return _characterManager; }

		bool IsRunning() const { return _isRunning; }
		TimeType CurrentTime() const { return _currentTime; }

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

			//LOG_WRITELINE("Q: ", _actionQueue.ToString());

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
		
		SimulationConsoleLog _consoleLog{ std::bind(&Simulation::CurrentTime, this) };
		CombatLog _combatLog{};

		bool _isRunning = true;
	};

}