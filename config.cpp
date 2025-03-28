#include "config.h"
#include <cstdlib>
#include <cmath>

Config::Config(int _atoms, double _J, double _temperature) {

    J = _J;
    temperature = _temperature;

    //Calculate beta from parameters provided
    beta = 1/(boltzmannConstant*temperature);

    atoms.resize(_atoms);

    //Populate the atoms vector with random spins of either +1 or -1
    for (int i = 0; i < _atoms; ++i) {
        atoms[i] = randomOne();
    }

}

//Method for generating a random +1 or -1
int Config::randomOne() {

    return (rand()%2 == 0 ? 1 : -1);

}

//Calculate the energy of interaction for an atom using its index in the atoms vector
//The spin of the atom can also be flipped for the calculation using the flip parameter
double Config::calculateEnergy(int atom, int flip=1) {

    double energyChange;

    //Boundary conditions for the first and last atom in the line are accounted for

    if (atom == atoms.size()-1) {

        energyChange = -J*atoms[atom]*flip*atoms[atom-1];

    } else {

        energyChange = (-J*atoms[atom]*flip*atoms[atom+1]);

    }

    return energyChange;
}


//Simulate the configuration for a given number for iterations
void Config::simulate(int iterations) {

    for (int i = 0; i < iterations; ++i) {
        
        //A random atom is selected each iteration
        int selection = rand()%(atoms.size()+1);

        //The energy change of flipping the atom's spin is calculated using the calculateEnergy method
        double energyChange = calculateEnergy(selection, -1)-calculateEnergy(selection);
        
        //The probability of this change is calculated using the partition function
        double probability = exp(-beta*energyChange);

        //The probability is capped at 1
        if (probability > 1) probability = 1;

        //The probability is compared to a random number between 0 and 1, and the atom's spin is flipped depending on this
        if ((rand()%100000)/1e5 < probability) {

            atoms[selection] *= -1;
        
        }

    }

}

double Config::calculateTotalEnergy() {

    double total = 0;

    for (int i = 0; i < atoms.size(); ++i) {
        
        total += calculateEnergy(i);

    }

    return total;

}

double Config::calculateTotalMagnetism() {

    double total = 0;

    for (int i = 0; i < atoms.size(); ++i) {
        
        total += atoms[i];

    }

    return total;

}

