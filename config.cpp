#include "config.h"
#include <cstdlib>

Config::Config(int _atoms, double _J) {

    J = _J;

    atoms.resize(_atoms);

    for (int i = 0; i < _atoms; ++i) {
        atoms[i] = randomOne();
    }

}

int Config::randomOne() {

    return (rand()%2 == 0 ? 1 : -1);

}

double Config::calculateEnergyChange(int atom) {

    double energyChange;

    if (atom == 0) {

        energyChange = -J*atoms[atom]*atoms[atom+1];

    } else if (atom == atoms.size()-1) {

        energyChange = -J*atoms[atom]*atoms[atom-1];


    } else {

        energyChange = (-J*atoms[atom]*atoms[atom+1]) + (-J*atoms[atom]*atoms[atom-1]);

    }

    return energyChange;
}
