#include <iostream>
#include "config.cpp"
#include <fstream>
#include <sstream>


int main() {

    std::ofstream output;

    int seed = 123500;

    int num_atoms = 100;
    double J = 1;
    std::vector<double> temperatures = {1e15, 1e20, 1e21, 1e22, 2.5e22, 5e22, 7.5e22, 1e23, 2.5e23, 5e23, 7.5e23, 1e24, 1e25, 1e26, 1e27, 1e28};
    
    int numConfigs = 1000;
    int iterations = 2000;

    // std::vector<Config> configurations;

    for (int t = 0; t < temperatures.size(); ++t) {

        srand(seed);

        double temperature = temperatures[t];
        
        std::stringstream filename;
        filename << "output/temp_" << t;
        output.open(filename.str());

        output << "Temperature " << temperature << std::endl;
        output << "config,energy,magnetism" << std::endl;

        for (int i = 0; i < numConfigs; ++i) {

            Config new_config = Config(num_atoms, J, temperature);
            new_config.simulate(iterations);
            // configurations.push_back(new_config);
            output << i << "," << new_config.calculateTotalEnergy() << "," << new_config.calculateTotalMagnetism() << std::endl;

            // std::cout << "\nConfiguration " << i+1 << "\nTotal Energy: " << new_config.calculateEnergy() << "\nMagnetisation: " << new_config.calculateMagnetism() << "\n";

        }

        output.close();


    }

    return 0;

}


