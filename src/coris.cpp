#include <coris.h>

#include <iostream>
#include <vector>
#include <thread>
#include <format>
#include <cstdio>

namespace coris
{

    void Worker(std::size_t N)
    {
        for(int i = 0; i < 10; ++i)
        {
            std::cout<<N <<":"<<i<<std::endl;
        }
    }

    Coris::Coris(std::size_t numberOfWorkerThreads)
    {
        std::puts(std::format("coris init on {}", numberOfWorkerThreads).c_str());
        _workerThreads.reserve(numberOfWorkerThreads);

        for(auto i = numberOfWorkerThreads; i > 0; --i)
        {
            _workerThreads.emplace_back(&Worker, i);
        }
    }

    Coris::~Coris()
    {
        _workerThreads.clear();
    }

}