#pragma once

#include <array>

namespace util
{

    /// <summary>
	/// A memory pool that allocates objects whose lifetime is coupled to the lifetime of the pool itself.
    /// </summary>
    /// <typeparam name="TSizeBytes">The total bytes of memory to allocate to the pool.</typeparam>
    template <size_t TSizeBytes>
    class StaticLifetimeMemoryPool
    {
    public:
        StaticLifetimeMemoryPool()
            : _next{ &_pool[0] }
        {
        }

        template <typename TType, typename... TArgs>
        TType& Allocate(TArgs&&... args)
        {
            static_assert(sizeof(TType) <= TSizeBytes, "The type to allocate is larger than the reserved pool size.");

            const size_t allocSize = sizeof(TType);
            if (_currentSize + allocSize > TSizeBytes)
                throw std::bad_alloc();

            TType* allocated = new (_next) TType(std::forward<TArgs&&>(args)...);

            _next += allocSize;
            _currentSize += allocSize;

            return *allocated;
        }

        template <typename TType>
        bool CanAllocate() noexcept
        {
            const size_t allocSize = sizeof(TType);
            return _currentSize + allocSize <= TSizeBytes;
        }

    private:
        unsigned char* _next;
        size_t _currentSize{ 0 };

        std::array<unsigned char, TSizeBytes> _pool{};
    };

}