//
// Created by hidie on 2020. 02. 02..
//

#ifndef GOL_HEX_CELL_H
#define GOL_HEX_CELL_H
/**
 * Cell states, which are constant short values.
 */
namespace cell_consts {

    /**
     * There are invalid cells. They exist because of the way how the hexagonal grid is represented in the matrix.
     */
    const short INVALID = -1;
    const short DEAD = 0;
    const short ALIVE = 1;

}

/**
 * Representation of GoL cells, and methods operating on them.
 */
class Cell {

private:

    short state;

public:

    Cell() = default;

    explicit Cell(short life) : state(life) {}

    ~Cell() = default;

    void kill() {
        this->state = cell_consts::DEAD;
    }

    void live() {
        this->state = cell_consts::ALIVE;
    }

    void invalidate(){
        this->state = cell_consts::INVALID;
    }

    bool isDead() {
        return this->state == cell_consts::DEAD;
    }

    bool isAlive() {
        return this->state == cell_consts::ALIVE;
    }

    bool isValid() {
        return this->state == cell_consts::INVALID;
    }

    short getState() {
        return state;
    }

};

#endif //GOL_HEX_CELL_H
