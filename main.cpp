// #include <random>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

double calculateEnergy(int selection, int atoms[], double J, int flip=1) {

    double energy;

    if (selection == 0) {

        energy = -J*atoms[selection]*flip*atoms[selection+1];

    } else if (selection == 100-1) {

        energy = -J*atoms[selection]*flip*atoms[selection-1];


    } else {

        energy = (-J*atoms[selection]*flip*atoms[selection+1]) + (-J*atoms[selection]*flip*atoms[selection-1]);

    }

    return energy;
}

int main() {

    int seed = 1234;

    double J  = 1;
    double temperature = 298;
    double beta = 1/(1.381e-23*temperature);

    std::vector<int> possible_iterations;

    for (int i = 1; i < 8; ++i) {

        possible_iterations.push_back(1*pow(10, i));

    }


    std::ofstream output;

    output.open("output.txt");

    output << "iterations,energy,magnetisation" << std::endl;

    for (int p = 0; p < possible_iterations.size(); ++p) {
        
        srand(seed);

        int num_atoms = 100;

        int atoms[num_atoms];

        for (int i = 0; i < num_atoms; ++i) {

            int state = rand()%2 == 0 ? 1 : -1;

            atoms[i] = state;


        }


        int iterations = possible_iterations[p];

        for (int i = 0; i < iterations; ++i) {

            int selection = rand()%(num_atoms+1);

            double energy_change = calculateEnergy(selection, atoms, J, -1) - calculateEnergy(selection, atoms, J);
            
            double probability = exp(-beta*energy_change);
            // std::cout << energy_change;

            if (probability > 1) probability = 1;

            if ((rand()%100000)/1e5 < probability) {

                atoms[selection] *= -1;
            
            }

        }

        double total_energy = 0;
        int magnetisation = 0;

        for (int i = 0; i < num_atoms; ++i) {
            total_energy += calculateEnergy(i, atoms, J);
            magnetisation += atoms[i];
        }

        std::cout << "\n iterations: " << iterations << "\n total energy: " << total_energy << " \n mag: " << magnetisation << "\n";

        output << iterations << "," << total_energy << "," << magnetisation << std::endl;

    }

    output.close();


    return 0;


}
