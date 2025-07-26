#include "ConsoleLogEventWriter.h"

#include <Simulation/Simulation.h>
#include <Simulation/SimulationConsoleLog.h>

#include <magic_enum/magic_enum.hpp>

namespace sim
{
	/*static*/
	void ConsoleLogEventWriter::Write(const Simulation& simulation, const CombatLog::EventInfo& eventInfo)
	{
		switch (eventInfo.eventType)
		{
			case EventType::Info:
				Write(simulation, static_cast<const InfoEventData&>(eventInfo.eventData));
				break;

			case EventType::Damage:
				Write(simulation, static_cast<const DamageEventData&>(eventInfo.eventData));
				break;

			case EventType::Miss:
				Write(simulation, static_cast<const MissEventData&>(eventInfo.eventData));
				break;

			default:
				Write(simulation, eventInfo.eventData);
				break;
		}
	}

	/*static*/
	void ConsoleLogEventWriter::Write(const Simulation& simulation, const EventData& eventData)
	{
		const SimulationConsoleLog& consoleLog = simulation.GetConsoleLog();
		consoleLog.WriteLine("Unknown combat log event.");
	}

	/*static*/
	void ConsoleLogEventWriter::Write(const Simulation& simulation, const InfoEventData& eventData)
	{
		const SimulationConsoleLog& consoleLog = simulation.GetConsoleLog();
		consoleLog.WriteLine(eventData.message);
	}

	/*static*/
	void ConsoleLogEventWriter::Write(const Simulation& simulation, const DamageEventData& eventData)
	{
		const SimulationConsoleLog& consoleLog = simulation.GetConsoleLog();
		const CharacterManager& characterManager = simulation.GetCharacterManager();

		const Character& source = *characterManager.TryGet<Character>(eventData.sourceId);
		const Character& target = *characterManager.TryGet<Character>(eventData.targetId);
		consoleLog.WriteLine(source.GetCharacterIdData().name, " swings at ", target.GetCharacterIdData().name, " for ", std::floor(eventData.damageAmount), ".");
	}

	/*static*/
	void ConsoleLogEventWriter::Write(const Simulation& simulation, const MissEventData& eventData)
	{
		const SimulationConsoleLog& consoleLog = simulation.GetConsoleLog();
		const CharacterManager& characterManager = simulation.GetCharacterManager();

		const Character& source = *characterManager.TryGet<Character>(eventData.sourceId);
		const Character& target = *characterManager.TryGet<Character>(eventData.targetId);
		consoleLog.WriteLine(source.GetCharacterIdData().name, " missed ", target.GetCharacterIdData().name, " (", magic_enum::enum_name(eventData.missType), ").");
	}

}