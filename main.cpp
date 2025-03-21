#include <iostream>
#include "config.cpp"
#include <fstream>

int main() {

    std::ofstream output;

    int seed = 123500;

    srand(seed);

    int num_atoms = 100;
    double J = 1;
    double temperature = 298;
    
    int numConfigs = 100;
    int iterations = 20000;

    std::vector<Config> configurations;

    output.open("output.txt");

    output << "config,energy,magnetism" << std::endl;

    for (int i = 0; i < numConfigs; ++i) {

        Config new_config = Config(num_atoms, J, temperature);
        new_config.simulate(iterations);
        configurations.push_back(new_config);

        output << i << "," << new_config.calculateEnergy() << "," << new_config.calculateMagnetism() << std::endl;

        // std::cout << "\nConfiguration " << i+1 << "\nTotal Energy: " << new_config.calculateEnergy() << "\nMagnetisation: " << new_config.calculateMagnetism() << "\n";

    }

    output.close();

    return 0;

}


