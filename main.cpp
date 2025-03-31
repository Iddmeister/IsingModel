#include <iostream>
#include "configcontainer.cpp"
//Included library for handling strings for output file names
#include <sstream>


int main() {
    
    //Seed for each temperature simulation
    int seed = 12345678;

    //Length of grid of atoms, the number of atoms will be this squared
    int num_atoms = 100;
    //Parameters for simulation
    int numConfigs = 1000;
    int iterations = 1e5;

    double J = 1;

    std::vector<double> temperatures = {1e20, 2.5e22, 5e22, 7.5e22, 1e23, 2.5e23, 5e23, 7.5e23, 1e25, 1e27};

    for (int t = 0; t < temperatures.size(); ++t) {

        double temperature = temperatures[t];

        ConfigContainer container = ConfigContainer(numConfigs, num_atoms, temperature, seed, J);

        container.simulate(iterations);
        std::stringstream filename;
        filename << "output/temperature_" << t << ".csv";
        container.outputResults(filename.str());

    }

    return 0;

}


