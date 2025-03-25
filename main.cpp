#include <iostream>
#include "config.cpp"
#include <fstream>
#include <sstream>


int main() {

    std::ofstream output;

    int seed = 123456;

    // int num_atoms = 100;
    int num_atoms = 100;

    double J = 1;
    std::vector<double> temperatures = {298, 1e3, 1e4, 1e10, 1e15, 1e20, 1e21, 1e22, 2.5e22, 5e22, 7.5e22, 1e23, 1e24, 1e25, 1e26, 1e27};
    
    // int numConfigs = 1000;
    // int iterations = 20000;
    int numConfigs = 1000;
    int iterations = 20000;

    // std::vector<Config> configurations;rand()%100000)/1e5

    for (int t = 0; t < temperatures.size(); ++t) {


        srand(seed);

        double temperature = temperatures[t];

        std::cout << "\nRunning " << numConfigs << " configurations at " << temperature;
        
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


