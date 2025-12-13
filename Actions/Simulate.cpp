#include <iostream>
#include "simulate.h" 
using namespace std;

class Simulate {
private:
    
    double timeStep;
    double totalTime;
    double currentTime;

    
public:
    Simulate(double ts, double tt) : timeStep(ts), totalTime(tt), currentTime(0.0) 
    {   
    }

    
    void initialize() {
        cout << " Initializing Simulation" << endl;
    }

 
    void update() {
        currentTime += timeStep;
    }

    void run() {
        initialize();

        while (currentTime < totalTime) {
            update();
            
        }

        finalize();
    }

    
    void finalize() {
      cout << "Simulation Complete at t=   " << currentTime << endl;
        
    }
};


int main() {
    Simulator sim(0.1, 10.0);
    sim.run();
    return 0;
}