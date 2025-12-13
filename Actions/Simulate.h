#include <iostream>
using namespace std;


class Simulate {
private:
    double timeStep;
    double totalTime;
    double currentTime;

public:
   
    Simulate(double ts, double tt);

    void initialize();
    void update();
    void run();
    void finalize();
};

#endif