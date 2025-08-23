#include "Random.h"

#include <random>

namespace
{
    class RandomProviderStd
    {
	public:
		static void Initialize(std::optional<uint32_t> seed = std::nullopt)
		{
			if (seed)
				_random = std::mt19937_64{ *seed };
			else
				_random = std::mt19937_64{ std::random_device{}() };
		}

		static uint64_t Next()
		{
			std::uniform_int_distribution<std::mt19937_64::result_type> dist{};
			return dist(_random);
		}

		static uint64_t Next(uint64_t min, uint64_t max)
		{
			std::uniform_int_distribution<std::mt19937_64::result_type> dist{ min, max };
			return dist(_random);
		}
	private:
		static inline std::mt19937_64 _random{ std::random_device{}() };
    };
}

namespace
{
	using RandomImpl = RandomProviderStd;
}

namespace util
{
    /*static*/
    void Random::Initialize(std::optional<uint32_t> seed)
    {
		RandomImpl::Initialize(seed);
    }

    /*static*/
    uint64_t Random::Next()
    {
		return RandomImpl::Next();
    }

    /*static*/
    uint64_t Random::Next(uint64_t min, uint64_t max)
    {
		return RandomImpl::Next(min, max);
    }
}