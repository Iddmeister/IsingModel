//Vector library included for list of atoms
#include <vector>

//Definition of class to hold each configuration of the system
class Config {

    public:

        //Constructor takes length of grid of atoms, J value and temperature of system
        //Constructor does not support non-square grids
        Config(int atoms, double J, double temperature);
        
        //Public methods to simulate system and retrieve calculation information from object
        double calculateTotalEnergy();
        double calculateTotalMagnetism();
        void simulate(int iterations);


    private:

        //Private member variables used in energy calculations
        double boltzmannConstant = 1.381e-23;
        double J;
        double temperature;
        double beta;

        std::vector<std::vector<int>> simulationDirections = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        //2D vector to hold grid of atom spins
        std::vector<std::vector<int>> atoms;

        //Private methods used during construction of object and energy calculations
        int randomOne();
        bool insideBounds(int x, int y);
        double calculateEnergy(int atomX, int atomY, std::vector<std::vector<int>> directions, int flip);

};