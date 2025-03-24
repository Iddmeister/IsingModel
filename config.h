#include <vector>

class Config {

    public:

        Config(int atoms, double J, double temperature);
        double J;
        double temperature;
        double beta;

        double calculateEnergyChange(int atomX, int atomY);
        double calculateEnergy();
        double calculateMagnetism();
        void simulate(int iterations);


    private:

        double boltzmannConstant = 1.381e-23;
        int randomOne();
        bool insideBounds(int x, int y);
        std::vector<std::vector<int>> atoms;


};