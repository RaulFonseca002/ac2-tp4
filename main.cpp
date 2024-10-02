#include "ula.hpp"
#include <stdio.h>

int main(int argc, char const *argv[])
{

    ula u(100);
    u.setMem("testula.hex");
    u.run();
    return 0;
}
