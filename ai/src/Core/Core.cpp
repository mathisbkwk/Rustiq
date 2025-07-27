
#include "Core.hpp"
#include "DataLoader/DataLoader.hpp"
#include <iostream>

namespace rustiq {
    int Core::run(int ac, char **av)
    {
        if (ac < 0 || !av || !av[1]) {
            std::cerr << "Invalid Arguments." << std::endl;
            return 84;
        }
        this->safeLookup([this, av] {
            this->isRunning = true;
            rustiq::DataLoader dataLoader(av[1]);
            
            dataLoader.printChunks();
        });
        return 0;
    }
}