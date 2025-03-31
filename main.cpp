#include <iostream>
#include "configcontainer.cpp"
//Included library for handling strings for output file names
#include <sstream>
#include <cstdlib>



int main(int argc, char* argv[]) {  

    int numAtoms = 100;
    int numConfigs = 1000;
    int iterations = 1e5;
    double J = 1;
    int seed = 12345678;

    std::string outputDirectory;

    std::vector<double> temperatures = {1e20, 2.5e22, 5e22, 7.5e22, 1e23, 2.5e23, 5e23, 7.5e23, 1e25, 1e27};

    //Pulling arguments from the command line with default values and error messages for incorrect inputs
    try {numAtoms = argc > 1 ? std::stoi(argv[1]) : 100;} catch (...) {std::cout << "\nError in number of atoms input\n\n"; return 0;};
    try {numConfigs = argc > 2 ? std::stoi(argv[2]) : 1000;} catch (...) {std::cout << "\nError in number of configurations input\n\n"; return 0;};
    try {iterations = argc > 3 ? std::stoi(argv[3]) : 1e5;} catch (...) {std::cout << "\nError in number of iterations input\n\n"; return 0;};
    try {J = argc > 4 ? std::stof(argv[4]) : 1;} catch (...) {std::cout << "\nError in J input\n\n"; return 0;};
    try {seed = argc > 5 ? std::stoi(argv[5]) : 12345678;} catch (...) {std::cout << "\nError in seed input\n\n"; return 0;};
    try {outputDirectory = argc > 6 ? argv[6] : "output_test";} catch (...) {std::cout << "\nError in output directory input\n\n"; return 0;};

    if (argc > 7) {

        temperatures.clear();

        //If there are enough arguments then loop through all of the arguments at the end of the supplied arguments and add them as temperatures to run
        for (int t = 7; t < argc; t++) {

            double new_temp;
            try {new_temp = std::stof(argv[t]);} catch (...) {std::cout << "\nError in temperature input\n\n"; return 0;};
            temperatures.push_back(new_temp);

        }

    }


    for (int t = 0; t < temperatures.size(); ++t) {

        double temperature = temperatures[t];

        ConfigContainer container = ConfigContainer(numConfigs, numAtoms, temperature, seed, J);

        container.simulate(iterations);
        std::stringstream filename;
        filename << outputDirectory << "/temperature_" << t << ".csv";
        container.outputResults(filename.str());

    }

    return 0;

}


