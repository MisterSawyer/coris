#include <cstdio>
#include <format>
#include <chrono>
#include <coris.h>

int main(int argc, char * argv[])
{
    using namespace std::literals::chrono_literals;
    std::puts("coris stared");
    std::puts(std::format("argc: {}", argc).c_str());
    
    coris::Coris coris(4);
    std::this_thread::sleep_for(2000ms);

    std::puts("coris ended");
    return 0;
}