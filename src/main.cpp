#include <cstdio>
#include <format>

#include <coris.h>

int main(int argc, char * argv[])
{
    std::puts("coris stared");
    std::puts(std::format("argc: {}", argc).c_str());
    
    coris::Coris coris(4);


    std::puts("coris ended");
    return 0;
}