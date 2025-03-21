#include "config.h"
#include <cstdlib>

Config::Config(int _atoms) {

    atoms.resize(_atoms);

    for (int i = 0; i < _atoms; ++i) {
        atoms[i] = randomOne();
    }

}

int Config::randomOne() {

    return (rand()%2 == 0 ? 1 : -1);

}