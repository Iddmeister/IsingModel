// #include <random>
#include <cstdlib>
#include <iostream>
#include <cmath>

double calculate_energy(int selection, int atoms[], double J) {

    double energy_change;

    if (selection == 0) {

        energy_change = -J*atoms[selection]*atoms[selection+1];

    } else if (selection == 100-1) {

        energy_change = -J*atoms[selection]*atoms[selection-1];


    } else {

        energy_change = (-J*atoms[selection]*atoms[selection+1]) + (-J*atoms[selection]*atoms[selection-1]);

    }

    return energy_change;
}

int main() {

    int seed = 1234;

    srand(seed);

    double J  = 1;
    double temperature = 298;
    double beta = 1/(1.381e-23*temperature);

    int num_atoms = 100;

    int atoms[num_atoms];

    for (int i = 0; i < num_atoms; ++i) {

        int state = rand()%2 == 0 ? 1 : -1;

        atoms[i] = state;

    // std::cout << atoms[i] << "\n";

    }

    int iterations = 200000;

    for (int i = 0; i < iterations; ++i) {

        int selection = rand()%(num_atoms+1);

        double energy_change = calculate_energy(selection, atoms, J);
        
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
        total_energy += calculate_energy(i, atoms, J);
        magnetisation += atoms[i];
    }

    std::cout << "\n total energy: " << total_energy << " \n mag: " << magnetisation << "\n";

    return 0;


    // std::mt19937 gen = std::mt19937(seed);

}
