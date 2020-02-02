//
// Created by hidie on 2020. 02. 02..
//

#ifndef GOL_HEX_SIMULATION_H
#define GOL_HEX_SIMULATION_H

#include "environment.h"
#include "rule_system.h"

class Simulation {

private:

    Environment environment;
    RuleSystem ruleSystem;
    unsigned int generation = 0;


    Simulation(Environment &environment, RuleSystem &ruleSystem) {
        this->environment = environment;
        this->ruleSystem = ruleSystem;
    }

    void run() {

    }
};

#endif //GOL_HEX_SIMULATION_H
