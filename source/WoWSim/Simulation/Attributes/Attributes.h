#pragma once

#include "PrimaryAttributes.h"

namespace sim
{

	struct Attributes
	{
		PrimaryAttributes primaryAttributes{};

		Attributes() {}

		Attributes(PrimaryAttributes attributesIn)
			: primaryAttributes{ attributesIn }
		{
		}
	};

}