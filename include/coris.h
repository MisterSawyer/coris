#pragma once
#include <utility>
#include <array>
#include <vector>
#include <thread>
#include <atomic>
#include <stop_token>

namespace coris
{
    using counter_id = std::size_t;
    using worker_id = std::size_t;
    using counter_value = int;

    class Coris final
    {
        public:
            Coris(std::size_t numberOfWorkerThreads);
            ~Coris();

            template<class Job>
            counter_id Run(Job);

            template<class Job, std::size_t N>
            counter_id Run(std::array<Job, N>);

            void Wait(counter_id, counter_value);

        protected:
            bool Init();
            void Clear();

            void Worker(std::stop_token, worker_id);

        private:
            const std::size_t _numberOfWorkerThreads;
            std::vector<std::jthread> _workerThreads;
    };
}

int main(int argc, char * argv[]);
