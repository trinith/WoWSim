#pragma once

#include <Simulation/PlayerCharacter.h>
#include <Simulation/UniqueId.h>

#include <OptionalRef.h>

#include <variant>

namespace sim
{
    class CharacterManager
    {
    public:

        uint64_t CreateCharacter(CharacterIdentifierData data, Attributes attributes)
        {
            const uint64_t id = UniqueId::Next<UniqueId::Type::Character>();
            _repo.emplace(id, Character{ id, std::move(data), std::move(attributes) });
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

    private:
        using StorageType = std::variant<
            Character,
            PlayerCharacter
        >;

        using RepositoryType = std::unordered_map<uint64_t, StorageType>;

        RepositoryType _repo{};
    };
}