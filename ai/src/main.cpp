
#include "DataLoader/DataLoader.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac < 0 || !av || !av[1]) {
        std::cerr << "Invalid Arguments." << std::endl;
        return 84;
    }
    rustiq::DataLoader dataLoader(av[1]);
    
    dataLoader.printChunks();
}