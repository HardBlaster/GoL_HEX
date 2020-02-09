//
// Created by hidie on 2020. 02. 02..
//

#ifndef GOL_HEX_RULE_SYSTEM_H
#define GOL_HEX_RULE_SYSTEM_H

#include <algorithm>
#include <set>

/**
 * Represent the set of rules, which is applied to evolve the simulation.
 */
class RuleSystem {

private:

    /**
     * The following sets are containing the number of neighbors required for a cell to born, remain the current state
     * or become dead.
     */
    std::set<int> born;
    std::set<int> stable;
    std::set<int> dead;

public:

    RuleSystem() = default;

    RuleSystem(std::set<int> &born, std::set<int> &stable, std::set<int> &dead) {
        this->born = born;
        this->stable = stable;
        this->dead = dead;
    }

    ~RuleSystem() = default;

    /**
    * Judges in what state a cell should be in the next generation. It changes the state attribute of the given cell
    * object.
    *
    * @param cell the cell object representing the cell in question.
    * @param neighbors the number of neighbors the cell has.
    */
    char judge(int neighbors) {
        if (stable.find(neighbors) == stable.end()) {

            if (born.find(neighbors) != born.end()) {
                return 'b';
            } else {
                return 'd';
            }

        } else {
            return 's';
        }
    }

    const std::set<int> &getBorn() const {
        return born;
    }

    void setBorn(const std::set<int> &born) {
        RuleSystem::born = born;
    }

    const std::set<int> &getStable() const {
        return stable;
    }

    void setStable(const std::set<int> &stable) {
        RuleSystem::stable = stable;
    }

    const std::set<int> &getDead() const {
        return dead;
    }

    void setDead(const std::set<int> &dead) {
        RuleSystem::dead = dead;
    }

};
#endif //GOL_HEX_RULE_SYSTEM_H
