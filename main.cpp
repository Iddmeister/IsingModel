#include <iostream>
#include "config.cpp"
#include <fstream>
//Included library for handling strings for output file names
#include <sstream>


int main() {
    
    //Seed for each temperature simulation
    int seed = 12345678;

    //Length of grid of atoms, the number of atoms will be this squared
    int num_atoms = 100;
    //Parameters for simulation
    // int numConfigs = 10000;

    double J = 1;
    //Vector to hold all temperatures that the simulation will be run at
    std::vector<double> possible_iterations;

    for (int i = 0; i < 8; ++i) {
        possible_iterations.push_back(pow(10, i));
    }

    possible_iterations.push_back(2e7);

    double temperature = 1e14;

    //Declare object to handle output files
    std::ofstream output;

    output.open("output.csv");

    //Results are output in csv format
    output << "iterations,energy,magnetism" << std::endl;

    for (int i = 0; i < possible_iterations.size(); ++i) {

        //Seed the randomness for each temperature simulation
        srand(seed);

        int iterations = possible_iterations[i];


        std::cout << "Running at " << temperature << "K with " << iterations << " iterations each" << std::endl;
        



        //Create configuration object
        Config new_config = Config(num_atoms, J, temperature);

        new_config.simulate(iterations);

        //Output results to the output file
        // output << i << "," << new_config.calculateTotalEnergy() << "," << new_config.calculateTotalMagnetism() << std::endl;
        std::tuple t = new_config.calculateTotalEnergyAndMagnetism();
        double totalEnergy = std::get<0>(t);
        double totalMagnetism= std::get<1>(t);

        output << possible_iterations[i] << "," << totalEnergy << "," << totalMagnetism << std::endl;

    }

    output.close();

    return 0;

}


