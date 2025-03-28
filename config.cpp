#include "config.h"
#include <cstdlib>
#include <cmath>

Config::Config(int _atoms, double _J, double _temperature) {

    J = _J;
    temperature = _temperature;
    beta = 1/(boltzmannConstant*temperature);

    atoms.resize(_atoms);

    for (int x = 0; x < _atoms; ++x) {
        atoms[x].resize(_atoms);
        for (int y = 0; y < _atoms; ++y) {
            atoms[x][y] = randomOne();
        }

    }

}

int Config::randomOne() {

    return (rand()%2 == 0 ? 1 : -1);

}

bool Config::insideBounds(int x, int y) {

    return (x >= 0 && x < atoms.size() && y >= 0 && y < atoms.size());

}

double Config::calculateEnergy(int atomX, int atomY, int flip=1) {

    double energy;

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    for (int d = 0; d < sizeof(directions); ++d) {

        if (insideBounds(atomX+directions[d][0], atomY+directions[d][1])) {

            energy += (-J*atoms[atomX+directions[d][0]][atomY+directions[d][1]]*atoms[atomX][atomY]*flip);

        }

    }

    return energy;
}


void Config::simulate(int iterations) {

    for (int i = 0; i < iterations; ++i) {

        int selectionX = rand()%(atoms.size());
        int selectionY = rand()%(atoms.size());

        double energyChange = calculateEnergy(selectionX, selectionY, -1) - calculateEnergy(selectionX, selectionY);
        
        double probability = exp(-beta*energyChange);

        if (probability > 1) probability = 1;

        if ((rand()%100000)/1e5 < probability) {

            atoms[selectionX][selectionY] *= -1;
        
        }

    }

}

double Config::calculateTotalEnergy() {

    double total = 0;

    for (int x = 0; x < atoms.size(); ++x) {
        
        for (int y = 0; y < atoms.size(); ++y) {
            total += calculateEnergy(x, y);
        }

    }

    return total;

}

double Config::calculateTotalMagnetism() {

    double total = 0;

    for (int x = 0; x < atoms.size(); ++x) {
        
        for (int y = 0; y < atoms.size(); ++y) {
            total += atoms[x][y];
        }

    }

    return total;

}

double* Config::calculateTotalEnergyMagnetism() {

    double total_energy = 0;
    double magnetism = 0;

    for (int x = 0; x < atoms.size(); ++x) {
        
        for (int y = 0; y < atoms.size(); ++y) {
            total_energy += calculateEnergy(x, y);
            magnetism += atoms[x][y];
        }

    }

    static double values[2] = {total_energy, magnetism};

    return values;

}

