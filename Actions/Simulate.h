#include <iostream>
using namespace std;


class Simulate : public Action {

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

    Simulate(ApplicationManager* pApp);
    virtual ~Simulate();

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

