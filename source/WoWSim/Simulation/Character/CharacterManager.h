#pragma once

#include <Simulation/UniqueId.h>
#include <Simulation/Character/MobCharacter.h>
#include <Simulation/Character/PlayerCharacter.h>

#include <OptionalRef.h>

#include <variant>

namespace sim
{
    class CharacterManager
    {
    public:
        uint64_t CreateMobCharacter(CharacterIdentifierData data, PrimaryAttributes baseAttributes)
        {
            const uint64_t id = UniqueId::Next<UniqueId::Type::Character>();
            _repo.emplace(id, MobCharacter{ id, std::move(data), std::move(baseAttributes) });
            return id;
		}

        uint64_t CreatePlayerCharacter(CharacterIdentifierData data, PlayerIdentifierData playerIdData)
        {
            const uint64_t id = UniqueId::Next<UniqueId::Type::Character>();
            _repo.emplace(id, PlayerCharacter{ id, std::move(data), std::move(playerIdData) });
            return id;
        }

        template <typename TCharacterType>
            requires std::is_base_of_v<Character, TCharacterType>
        OptionalRef<const TCharacterType> TryGet(uint64_t id) const
        {
            if (auto findResult = _repo.find(id); findResult != _repo.end() && std::holds_alternative<TCharacterType>(findResult->second))
                return OptionalRef<const TCharacterType>{std::get<TCharacterType>(findResult->second)};

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

        // GT_TODO: This needs to be changed but it's good enough for now.
        OptionalRef<const Character> TryGet(uint64_t id) const
        {
            if (auto findResult = _repo.find(id); findResult != _repo.end())
            {
                if (std::holds_alternative<MobCharacter>(findResult->second))
                    return OptionalRef<const Character>{std::get<MobCharacter>(findResult->second)};
                else if (std::holds_alternative<PlayerCharacter>(findResult->second))
                    return OptionalRef<const Character>{std::get<PlayerCharacter>(findResult->second)};
            }

			return std::nullopt;
        }

        OptionalRef<Character> TryGet(uint64_t id)
        {
            OptionalRef<const Character> result = const_cast<const CharacterManager*>(this)->TryGet(id);
            if (!result)
                return std::nullopt;

            return OptionalRef<Character>{const_cast<Character&>(result->get())};
        }

    private:
        using StorageType = std::variant<
            MobCharacter,
            PlayerCharacter
        >;

        using RepositoryType = std::unordered_map<uint64_t, StorageType>;

        // GT_TODO: This type should change. The variant isn't working so find another approach.
        RepositoryType _repo{};
    };
}