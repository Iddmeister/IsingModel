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
    int numConfigs = 1000;
    int iterations = 10000;

    double J = 1;
    //Vector to hold all temperatures that the simulation will be run at
    std::vector<double> temperatures = {1e15, 1e20, 1e21, 1e22, 2.5e22, 5e22, 7.5e22, 1e23, 2.5e23, 5e23, 7.5e23, 1e24, 1e25, 1e26, 1e27, 1e28};
    // std::vector<double> temperatures = {1e15};


    //Declare object to handle output files
    std::ofstream output;

    for (int t = 0; t < temperatures.size(); ++t) {

        //Seed the randomness for each temperature simulation
        srand(seed);

        double temperature = temperatures[t];

        std::cout << "Running " << numConfigs << " configurations at " << temperature << "K with " << iterations << " iterations each" << std::endl;
        
        //Create output file with unique name
        std::stringstream filename;
        filename << "output/temperature_" << t << ".csv";
        output.open(filename.str());

        //Write the temperature of the simulation to the first line of the output file
        output << "Temperature " << temperature << std::endl;
        //Results are output in csv format
        output << "config,energy,magnetism" << std::endl;

        for (int i = 0; i < numConfigs; ++i) {

            //Create configuration object
            Config new_config = Config(num_atoms, J, temperature);

            new_config.simulate(iterations);

            //Output results to the output file
            // output << i << "," << new_config.calculateTotalEnergy() << "," << new_config.calculateTotalMagnetism() << std::endl;
            std::tuple t = new_config.calculateTotalEnergyAndMagnetism();
            double totalEnergy = std::get<0>(t);
            double totalMagnetism= std::get<1>(t);

            output << i << "," << totalEnergy << "," << totalMagnetism << std::endl;


        }

        output.close();


    }

    return 0;

}


