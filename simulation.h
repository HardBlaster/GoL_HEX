//
// Created by hidie on 2020. 02. 02..
//

#ifndef GOL_HEX_SIMULATION_H
#define GOL_HEX_SIMULATION_H

#include "environment.h"

class Simulation {

private:

    Environment *environment;

public:

    Simulation(Environment *environment) {
        this->environment = environment;
    }

    void run(int maxGeneration) {
        for (int i = 0; i < maxGeneration; ++i) {
            environment->nextStep();
        }
    }
};

#endif //GOL_HEX_SIMULATION_H
