#include "configcontainer.h"
#include <fstream>


ConfigContainer::ConfigContainer(int numConfigs, int numAtoms, double temperature, int seed, double J) {

    this->temperature = temperature;

    srand(seed);

    for (int c = 0; c < numConfigs; c++) {

        //Create Config objects and add them to a vector
        Config new_config = Config(numAtoms, J, temperature, rand());
        configurations.push_back(new_config);

    }

}

void ConfigContainer::simulate(int iterations) {

    //Output message with information about the simulation
    std::cout << "Running " << configurations.size() << " configurations for " << iterations << " iterations at a temperature of " << temperature << std::endl;

    for (int c = 0; c < configurations.size(); c++) {

        //Simulate each configuration in the container for given
        configurations[c].simulate(iterations);

    }

}

void ConfigContainer::outputResults(std::string filename) {

    std::cout << "Writing results to " << filename << std::endl;

    std::ofstream output;

    output.open(filename);

    output << "Temperature " << temperature << std::endl;

    output << "config,energy,magnetism" << std::endl;

    for (int c = 0; c < configurations.size(); c++) {
        
        //Using tuple to unpack 2 return values from method
        std::tuple t = configurations[c].calculateTotalEnergyAndMagnetism();
        double totalEnergy = std::get<0>(t);
        double totalMagnetism= std::get<1>(t);

        output << c << "," << totalEnergy << "," << totalMagnetism << std::endl;

    }

    output.close();

}
