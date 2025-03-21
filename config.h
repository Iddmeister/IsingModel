#include <vector>

class Config {

    public:

        Config(int atoms, double J);
        double J;

        double calculateEnergyChange(int atom);


    private:

        int randomOne();
        std::vector<int> atoms;


};