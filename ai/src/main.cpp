
#include "Core/Core.hpp"

int main(int ac, char **av)
{
    rustiq::Core core;
    
    return core.run(ac, av);
}