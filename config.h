#include <vector>

//Class to hold individual configurations of atoms, simulate the spin flips and calculate energy/magnetism
class Config {

    public:

        //Constructor for class requires the number of atoms, the value of J and the temperature of the configuration
        Config(int atoms, double J, double temperature);

        //Public methods for calculation of values and simulation
        double calculateTotalEnergy();
        double calculateTotalMagnetism();
        void simulate(int iterations);


    private:

        //Private member variables to hold information about the configuration
        double J;
        double temperature;
        double beta;
        double boltzmannConstant = 1.381e-23;

        //Method fo generating a random +1 or -1
        int randomOne();
        //Method for calculating energy of interaction of a single atom
        double calculateEnergy(int atom, int flip);
        //Vector to hold all atoms in the configuration
        std::vector<int> atoms;


};