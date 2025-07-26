#pragma once

#include <Simulation/CombatLog/CombatLog.h>

namespace sim
{
	class Simulation;

	class ConsoleLogEventWriter
	{
	public:
		static void Write(const Simulation& simulation, const CombatLog::EventInfo& eventInfo);

		static void Write(const Simulation& simulation, const EventData& eventData);
		static void Write(const Simulation& simulation, const InfoEventData& eventData);
		static void Write(const Simulation& simulation, const DamageEventData& eventData);
		static void Write(const Simulation& simulation, const MissEventData& eventData);
	};

}