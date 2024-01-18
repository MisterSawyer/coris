#pragma once
#include <coris.h>
#include <coroutine>

namespace coris
{
    template<class CoroutineType, class ValueType>
    struct Promise
    {
        CoroutineType get_return_object() 
        { 
            return {CoroutineType::from_promise(*this)}; 
        }

        std::suspend_always initial_suspend() noexcept 
        {
            _value = ValueType{};
            return {}; 
        }

        std::suspend_always final_suspend() noexcept
        { 
            return {};
        }

        std::suspend_always yield_value(ValueType value) noexcept
        { 
            _value = std::move(value);
            return {};
        }

        void return_value(ValueType value) 
        {
            _value = std::move(value);
        }

        void unhandled_exception() 
        {
        }

        constexpr inline const ValueType & Get() const noexcept {return _value;}

        ValueType _value;
    };
}