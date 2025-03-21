#include <iostream>
#include "config.cpp"


int main() {

    int seed = 123500;

    srand(seed);

    int num_atoms = 100;
    double J = 1;
    double temperature = 298;
    
    int numConfigs = 100;
    int iterations = 20000;

    std::vector<Config> configurations;

    for (int i = 0; i < numConfigs; ++i) {

        Config new_config = Config(num_atoms, J, temperature);
        new_config.simulate(iterations);
        configurations.push_back(new_config);
        std::cout << "\nConfiguration " << i+1 << "\nTotal Energy: " << new_config.calculateEnergy() << "\nMagnetisation: " << new_config.calculateMagnetism() << "\n";

    }

    return 0;

}


