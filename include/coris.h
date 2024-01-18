#pragma once
#include <utility>
#include <array>
#include <vector>
#include <thread>

namespace coris
{
    using counter_id = std::size_t;
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

        private:
            std::vector<std::jthread> _workerThreads;
    };
}

int main(int argc, char * argv[]);
