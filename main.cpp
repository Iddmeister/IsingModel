#include <cstdlib>
#include <iostream>
#include <cmath>

//This function takes an array of atoms and an index for the atom to calculate the energy of interaction for
//The value of J and whether or not to flip the state of the atom of interest are also included in the parameters
double calculateEnergy(int selection, int atoms[], double J, int flip=1) {

    double energy_change;

    //Boundary conditions for the first and last atom in the line are accounted for

    if (selection == 0) {

        energy_change = -J*atoms[selection]*flip*atoms[selection+1];

    } else if (selection == 100-1) {

        energy_change = -J*atoms[selection]*flip*atoms[selection-1];

    } else {

        energy_change = (-J*atoms[selection]*flip*atoms[selection+1]) + (-J*atoms[selection]*flip*atoms[selection-1]);

    }

    return energy_change;
}

int main() {

    //The randomness is seeded so that results can be repeated
    int seed = 1234;
    srand(seed);

    //Constants required for the algorithm are defined here
    double J  = 1;
    double temperature = 298;
    double beta = 1/(1.381e-23*temperature);

    //The number of atoms to simulate the spin of
    int num_atoms = 100;

    int atoms[num_atoms];

    for (int i = 0; i < num_atoms; ++i) {
        
        //All of the atoms are assigned a spin of -1 or +1 randomly
        int state = rand()%2 == 0 ? 1 : -1;

        atoms[i] = state;

    }

    //The number of iterations to simulate for
    int iterations = 200000;

    for (int i = 0; i < iterations; ++i) {

        //A random atom is selected each iteration
        int selection = rand()%(num_atoms+1);

        //The energy change of flipping the atom's spin is calculated using the calculateEnergy function
        double energy_change = calculateEnergy(selection, atoms, J, -1) - calculateEnergy(selection, atoms, J);
        
        //The probability of this change is calculated using the partition function
        double probability = exp(-beta*energy_change);

        //The probability is capped at 1
        if (probability > 1) probability = 1;

        //The probability is compared to a random number between 0 and 1, and the atom's spin is flipped depending on this
        if ((rand()%100000)/1e5 < probability) {

            atoms[selection] *= -1;
        
        }

    }

    double total_energy = 0;
    int magnetisation = 0;

    for (int i = 0; i < num_atoms; ++i) {

        //The total energy and magnetism are summed over every atom
        total_energy += calculateEnergy(i, atoms, J);
        magnetisation += atoms[i];
    }

    //The final values are output
    std::cout << "\n total energy: " << total_energy << " \n mag: " << magnetisation << "\n\n";

    return 0;


}
