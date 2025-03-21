#include <vector>

class Config {

    public:

        Config(int atoms, double J, double temperature);
        double J;
        double temperature;
        double beta;

        double calculateEnergyChange(int atom);
        double calculateEnergy();
        double calculateMagnetism();
        void simulate(int iterations);


    private:

        double boltzmannConstant = 1.381e-23;
        int randomOne();
        std::vector<int> atoms;


};