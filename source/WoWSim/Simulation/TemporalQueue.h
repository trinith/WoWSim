#pragma once

#include <deque>
#include <iostream>
#include <optional>
#include <sstream>

namespace sim
{

    template <typename T>
    concept TimeType = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

    template <TimeType TTime, typename TQueueType>
    class TemporalQueue
    {
    private:
        struct InternalType
        {
            TTime t;
            std::unique_ptr<TQueueType> data;

            friend std::ostream& operator<<(std::ostream& os, const InternalType& obj)
            {
                os << "{";
                os << "t=" << obj.t;
                os << ", data=";
                if (obj.data == nullptr)
                    os << "nullptr";
                else
                    os << *obj.data;
                os << "}";
                return os;
            }
        };
        using Q = std::deque<InternalType>;

    public:
        TemporalQueue()
            : _queue{}
        {
        }

        template <typename TActionType, typename ...TArgs>
        void Enqueue(TTime t, TArgs&&... args)
        {
            if (_queue.empty())
            {
                EnqueueAt<TActionType>(_queue.begin(), t, args...);
                return;
            }

            for (typename Q::iterator it = _queue.begin(); it != _queue.end(); ++it)
            {
                const InternalType& item = *it;
                if (t < item.t)
                {
                    EnqueueAt<TActionType>(it, t, args...);
                    return;
                }
            }

            EnqueueAt<TActionType>(_queue.end(), t, args...);
        }

        std::unique_ptr<TQueueType> Pop()
        {
            if (_queue.empty())
                return nullptr;

            InternalType& item = _queue.front();
            TTime t = item.t;
            std::unique_ptr<TQueueType> data = std::move(item.data);
            _queue.pop_front();

            AdvanceTime(t);

            return data;
        }

        TTime NextTime() const
        {
            if (_queue.empty())
                return 0;

            return _queue.front().t;
        }

        bool IsEmpty() const
        {
            return _queue.empty();
        }

        void Clear()
        {
            _queue.clear();
        }

        std::string ToString()
        {
            std::stringstream ss;
            ss << "{";
            bool first = true;
            for (auto&& item : _queue)
            {
                if (!first)
                    ss << ", ";
                first = false;
                ss << item;
            }
            ss << "}";
            return ss.str();
        }

    private:
        template <typename TType, typename ...TArgs>
        void EnqueueAt(typename Q::iterator it, TTime t, TArgs&&... args)
        {
            std::unique_ptr<TQueueType> data = std::make_unique<TType>(std::forward<TArgs&&>(args)...);
            _queue.emplace(it, t, std::move(data));
        }

        void AdvanceTime(TTime t)
        {
            for (auto&& item : _queue)
                item.t -= t;
        }

        Q _queue;
    };

}