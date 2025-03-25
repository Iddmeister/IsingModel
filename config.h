#include <vector>

class Config {

    public:

        Config(int atoms, double J, double temperature);
        double J;
        double temperature;
        double beta;
        double calculateTotalEnergy();
        double calculateTotalMagnetism();
        double* calculateTotalEnergyMagnetism();
        void simulate(int iterations);


    private:

        double boltzmannConstant = 1.381e-23;
        int randomOne();
        bool insideBounds(int x, int y);
        double calculateEnergy(int atomX, int atomY, int flip);
        std::vector<std::vector<int>> atoms;


};