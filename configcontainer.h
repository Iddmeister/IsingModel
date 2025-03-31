#include "config.cpp"
#include <string>

class ConfigContainer {

    public:

        ConfigContainer(int numConfigs, int numAtoms, double temperature, int seed, double J);
        void simulate(int iterations);
        void outputResults(std::string filename);

        double temperature;

    private:

        std::vector<Config> configurations;

};