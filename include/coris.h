#pragma once

#include <utility>
#include <array>
#include <vector>
#include <thread>
#include <atomic>
#include <stop_token>
#include <coroutine>

namespace coris
{
    using counter_value_t = int;
    using Counter = std::size_t;

    template<class JobType, class ValueType>
    class Promise;

    template<class JobType, class ValueType>
    class Promise
    {
        public:
        using job_type = JobType;
        using value_type = ValueType;

        job_type get_return_object() { return {job_type::from_promise(*this)}; }

        std::suspend_always initial_suspend() noexcept {
            _value = value_type{};
            return {}; 
        }

        std::suspend_always final_suspend() noexcept
        { 
            return {};
        }

        std::suspend_always yield_value(value_type value) noexcept
        { 
            _value = std::move(value);
            return {};
        }

        void return_value(value_type value) 
        {
            _value = std::move(value);
        }

        void unhandled_exception() 
        {

        }

        constexpr inline const value_type & Get() const noexcept {return _value;}

        private:
            value_type _value;
    };

    class Job : public std::coroutine_handle<Promise<Job, counter_value_t>>
    {
        public:
            using promise_type = Promise<Job, counter_value_t>;
            const promise_type::value_type & Get() const {return promise().Get();}
    };

    class Coris final
    {
        public:
            //
            Coris();
            //
            ~Coris();
            //
            constexpr inline Counter Run(Job job) {return Run(&job, 1);}
            //
            inline Counter Run(std::vector<Job> vec) {return Run(vec.data(), vec.size());}

            template<std::size_t N>
            constexpr inline Counter Run(std::array<Job, N> arr){return Run(arr.data(), N);}

            //
            void Wait(Counter, counter_value_t);
            //
            counter_value_t Check(Counter);

        protected:
            Counter Run(Job arr[], std::size_t N);

    };
}

int main(int argc, char * argv[]);
