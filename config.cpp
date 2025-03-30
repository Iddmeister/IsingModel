#include "config.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

Config::Config(int _atoms, double _J, double _temperature) {

    J = _J;
    temperature = _temperature;
    beta = 1/(boltzmannConstant*temperature);

    //Atoms vector resized to input parameter
    atoms.resize(_atoms);

    //All spins randomly set to +1 or -1
    for (int x = 0; x < _atoms; ++x) {
        //Each column of atoms vector resized to input parameter
        atoms[x].resize(_atoms);
        for (int y = 0; y < _atoms; ++y) {
            atoms[x][y] = randomOne();
        }

    }

}

//Method to generate a random +1 or -1, included for better readability
int Config::randomOne() {

    return (rand()%2 == 0 ? 1 : -1);

}

//Method to check whether an x and y coord is inside of the grid of atoms
bool Config::insideBounds(int x, int y) {

    return (x >= 0 && x < atoms.size() && y >= 0 && y < atoms.size());

}

//Method to calculate the energy of a single atoms interactions, the spin of the atom can be optionally flipped for the calculation
double Config::calculateEnergy(int atomX, int atomY, std::vector<std::vector<int>> directions, int flip=1) {

    double energy;
    
    for (int d = 0; d < directions.size(); ++d) {

        if (insideBounds(atomX+directions[d][0], atomY+directions[d][1])) {

            energy += (-J*atoms[atomX+directions[d][0]][atomY+directions[d][1]]*atoms[atomX][atomY]*flip);

        }

    }

    return energy;
}


//Method to simulate the system for a given number of iterations, this method directly edits the 2D atoms vector
void Config::simulate(int iterations) {

    for (int i = 0; i < iterations; ++i) {

        //Select random x, y coord inside of the 2D atoms vector
        int selectionX = rand()%(atoms.size());
        int selectionY = rand()%(atoms.size());

        //Calculate the energy change of flipping the spin of selected atom
        double energyChange = calculateEnergy(selectionX, selectionY, simulationDirections, -1) - calculateEnergy(selectionX, selectionY, simulationDirections);
        
        //Calculate probability of energyChange using partition function
        double probability = exp(-beta*energyChange);

        //Cap probability at 1
        if (probability > 1) probability = 1;

        //Check probability against random float betwwen 0 and 1
        if ((rand()%100000)/1e5 < probability) {
            
            //Flip the spin of th selcted atom
            atoms[selectionX][selectionY] *= -1;
        
        }

    }

}

double Config::calculateTotalEnergy() {

    double total = 0;

    for (int x = 0; x < atoms.size(); ++x) {
        
        for (int y = 0; y < atoms.size(); ++y) {

            std::vector<std::vector<int>> directions = {{1, 0}, {0, -1}};
            total += calculateEnergy(x, y, directions);

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

