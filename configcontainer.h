#include "config.cpp"
#include <string>

//Class to hold multiple configurations running at the same temperature
class ConfigContainer {

    public:

        //Public methods to simulate and output configuration results
        ConfigContainer(int numConfigs, int numAtoms, double temperature, int seed, double J);
        void simulate(int iterations);
        void outputResults(std::string filename);

        double temperature;

    private:

        std::vector<Config> configurations;

};