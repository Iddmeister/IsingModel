#include "config.h"
#include <cstdlib>
#include <cmath>

Config::Config(int _atoms, double _J, double _temperature) {

    J = _J;
    temperature = _temperature;
    beta = 1/(boltzmannConstant*temperature);

    atoms.resize(_atoms);

    for (int i = 0; i < _atoms; ++i) {
        atoms[i] = randomOne();
    }

}

int Config::randomOne() {

    return (rand()%2 == 0 ? 1 : -1);

}

double Config::calculateEnergy(int atom, int flip=1) {

    double energyChange;

    if (atom == 0) {

        energyChange = -J*atoms[atom]*flip*atoms[atom+1];

    } else if (atom == atoms.size()-1) {

        energyChange = -J*atoms[atom]*flip*atoms[atom-1];

    } else {

        energyChange = (-J*atoms[atom]*flip*atoms[atom+1]) + (-J*atoms[atom]*flip*atoms[atom-1]);

    }

    return energyChange;
}

void Config::simulate(int iterations) {

    for (int i = 0; i < iterations; ++i) {

        int selection = rand()%(atoms.size()+1);

        double energyChange = calculateEnergy(selection)-calculateEnergy(selection, -1);
        
        double probability = exp(-beta*energyChange);

        if (probability > 1) probability = 1;

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

