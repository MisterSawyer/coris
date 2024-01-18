#include <coris.h>

#include <iostream>
#include <vector>
#include <thread>
#include <format>
#include <cstdio>

namespace coris
{

    void Coris::Worker(std::stop_token token, worker_id id)
    {
        //Init thread
        while(token.stop_requested() == false)
        {
            std::puts(std::format("worker[{}]", id).c_str());
            for(int i=0; i < 10; ++i)std::cout<<i;
            std::cout<<std::endl;
            // Fetch Job
            // Execute
            // Check counters
        }
        // Exit thread
    }

    Coris::Coris(std::size_t N)
    : _numberOfWorkerThreads{N}
    {
        _workerThreads.reserve(_numberOfWorkerThreads);
        Init();
    }

    Coris::~Coris()
    {
        Clear();
    }

    bool Coris::Init()
    {
        for(worker_id id = 0; id < _numberOfWorkerThreads; ++id)
        {
            _workerThreads.emplace_back(&Worker, this, id);
        }

        return true;
    }

    void Coris::Clear()
    {
        for(auto & thread :_workerThreads )
        {
            thread.request_stop();
        }

        for(auto & thread :_workerThreads )
        {
            thread.join();
        }

        _workerThreads.clear();
    }
}