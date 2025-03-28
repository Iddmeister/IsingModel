#include <iostream>
#include "config.cpp"
#include <fstream>
#include <sstream>


int main() {

    //ofstream object used fro writing output to file
    std::ofstream output;

    //The randomness is seeded so that results can be repeated
    int seed = 1235;

    //Constants for all simulations are defined
    int num_atoms = 100;
    double J = 1;

    //A vector is used to hold all the temperatures that the configurations will be run at
    std::vector<double> temperatures = {1e15, 1e20, 1e21, 1e22, 2.5e22, 5e22, 7.5e22, 1e23, 2.5e23, 5e23, 7.5e23, 1e24, 1e25, 1e26, 1e27, 1e28};
    
    //The number of configurations to run for each temperature
    int numConfigs = 10000;
    //The number of iterations to run for the spin interaction simulation for each configuration
    int iterations = 10000;

    for (int t = 0; t < temperatures.size(); ++t) {

        //The randomness is seeded for each temperature for consistent results
        srand(seed);

        double temperature = temperatures[t];
        
        //A different output file is generated for each temperature
        //The name of the file is made unique
        std::stringstream filename;
        filename << "output/temperature_" << t << ".csv";
        output.open(filename.str());

        //The first line of the file contains the temperature that the configurations were run at
        output << "Temperature " << temperature << std::endl;
        //The file is written to in csv format
        output << "config,energy,magnetism" << std::endl;

        for (int i = 0; i < numConfigs; ++i) {
            
            //A configuration is created each iteration
            Config new_config = Config(num_atoms, J, temperature);
            //The configuration is then simulated for the defined number of iterations
            new_config.simulate(iterations);
            //The resulting energy and magnetism are written to the output file along with the configuration number
            output << i << "," << new_config.calculateTotalEnergy() << "," << new_config.calculateTotalMagnetism() << std::endl;

        }

        output.close();


    }

    return 0;

}


