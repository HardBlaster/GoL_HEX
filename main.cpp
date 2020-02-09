#include "simulation.h"

int main() {

    std::set<int> b, s, d;
    b.insert({0, 1, 2});
    s.insert({3, 4, 5});
    d.insert({6, 7, 8});

    auto *ruleSystem = new RuleSystem;
    ruleSystem->setBorn(b);
    ruleSystem->setStable(s);
    ruleSystem->setDead(d);

    auto *environment = new Environment(10, 10, 50);
    environment->setRuleSystem(ruleSystem);

    Simulation simulation(environment);

    simulation.run(15);

    return 0;
}