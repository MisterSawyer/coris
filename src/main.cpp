#include <cstdio>
#include <format>
#include <chrono>

#include <coris.h>

coris::Job SomeJob(int i)
{
    co_return 9 + i;
}

int main(int argc, char * argv[])
{
    std::puts(std::format("argc: {}", argc).c_str());
    coris::Coris coris;

    std::puts("coris stared");

    std::array<coris::Job, 10> jobs;
    coris::Counter cnt;

    for(int i=0; i<10; ++i)
    {
        jobs[i] = SomeJob(i);
    }

    cnt = coris.Run(jobs);
    coris.Wait(cnt, 10);

    coris.Run(SomeJob(3));

    std::puts("coris ended");
    return 0;
}