#pragma once

#include <Simulation/UniqueId.h>
#include <Simulation/Character/MobCharacter.h>
#include <Simulation/Character/PlayerCharacter.h>

#include <Util/Memory/StaticLifetimeMemoryPool.h>

#include <OptionalRef.h>

namespace sim
{
    class CharacterManager
    {
    public:
        template <typename TCharacterType, typename... TArgs>
			requires std::is_base_of_v<Character, TCharacterType>
        std::optional<uint64_t> CreateCharacter(TArgs&&... args)
        {
            if (!_memoryPool.CanAllocate<TCharacterType>())
                return std::nullopt;

            const uint64_t id = UniqueId::Next<UniqueId::Type::Character>();
			TCharacterType& character = _memoryPool.Allocate<TCharacterType>(id, std::forward<TArgs&&>(args)...);

            _charList.emplace_back(character);
            _charMap.emplace(id, &character);

			return id;
        }

        template <typename TCharacterType>
            requires std::is_base_of_v<Character, TCharacterType>
        OptionalRef<const TCharacterType> TryGet(uint64_t id) const
        {
            if (auto findResult = _charMap.find(id); findResult != _charMap.end())
                return OptionalRef<const TCharacterType>{*static_cast<const TCharacterType*>(findResult->second)};

            return std::nullopt;
        }

        template <typename TCharacterType>
            requires std::is_base_of_v<Character, TCharacterType>
        OptionalRef<TCharacterType> TryGet(uint64_t id)
        {
            OptionalRef<const TCharacterType> result = const_cast<const CharacterManager*>(this)->TryGet<TCharacterType>(id);
            if (!result)
                return std::nullopt;

			return OptionalRef<TCharacterType>{const_cast<TCharacterType&>(result->get())};
        }

		auto begin() const { return _charList.begin(); }
        auto end() const { return _charList.end(); }

    private:
        util::StaticLifetimeMemoryPool<4096> _memoryPool;
        std::vector<std::reference_wrapper<const Character>> _charList{};
        std::unordered_map<uint64_t, Character*> _charMap{};
    };
}