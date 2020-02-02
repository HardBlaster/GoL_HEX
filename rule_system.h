//
// Created by hidie on 2020. 02. 02..
//

#ifndef GOL_HEX_RULE_SYSTEM_H
#define GOL_HEX_RULE_SYSTEM_H

#include <algorithm>
#include <set>

class RuleSystem {

private:

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

    void judge(Cell &cell, int &neighbors) {
        if(stable.find(neighbors) == stable.end()) {

            if(born.find(neighbors) != born.end()) {
                cell.live();
            } else {
                cell.kill();
            }
        }
    }

    ~RuleSystem() = default;

};
#endif //GOL_HEX_RULE_SYSTEM_H
