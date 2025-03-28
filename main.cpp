#include <iostream>
#include "config.cpp"
#include <fstream>

int main() {

    std::ofstream output;

    int seed = 123500;

    srand(seed);

    int num_atoms = 100;
    double J = 1;
    double temperature = 1e24;
    
    int numConfigs = 50000;
    int iterations = 10000;

    std::vector<Config> configurations;

    output.open("output.csv");

    output << "config,energy,magnetism" << std::endl;

    for (int i = 0; i < numConfigs; ++i) {

        Config new_config = Config(num_atoms, J, temperature);
        new_config.simulate(iterations);
        configurations.push_back(new_config);

        output << i << "," << new_config.calculateTotalEnergy() << "," << new_config.calculateTotalMagnetism() << std::endl;

        // std::cout << "\nConfiguration " << i+1 << "\nTotal Energy: " << new_config.calculateEnergy() << "\nMagnetisation: " << new_config.calculateMagnetism() << "\n";

    }

    output.close();

    return 0;

}


