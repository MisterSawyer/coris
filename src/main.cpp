#include <cstdio>
#include <format>
#include <chrono>
#include <coris.h>
#include <coroutine>

#include "promise.h"

struct JobCoroutine : std::coroutine_handle<coris::Promise<JobCoroutine, int>>
{
    using promise_type = coris::Promise<JobCoroutine, int>;
};

JobCoroutine SomeJob()
{
    co_return 9;
}

int main(int argc, char * argv[])
{
    std::puts(std::format("argc: {}", argc).c_str());

    auto f = SomeJob();
    f.resume();
    std::puts(std::format("f: {}", f.promise().Get()).c_str());
    f.destroy();

    using namespace std::literals::chrono_literals;
    std::puts("coris stared");
    
    
    coris::Coris coris(4);
    std::this_thread::sleep_for(2ms);

    std::puts("coris ended");
    return 0;
}