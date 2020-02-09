//
// Created by hidie on 2020. 02. 02..
//

#ifndef GOL_HEX_ENVIRONMENT_H
#define GOL_HEX_ENVIRONMENT_H

#include <random>
#include "cell.h"
#include "rule_system.h"

class Environment {

private:

    /**
     * Multidimensional array of cell objects. It is supposed to represent a hexagonal grid, which is why every second
     * cell of a row is invalid. To determine if a cell is valid:
     * !((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)), where:
     * i -- row,
     * j -- column.
     */
    Cell **matrix = nullptr;
    /**
     * Multidimensional array containing the number of living neighbours of every cell. Number of neighbours of X-th
     * valid cell of Y-th row equals to neighbors[Y][X];
     */
    unsigned short **neighbors = nullptr;
    unsigned int width;
    unsigned int height;
    unsigned int generation = 0;

    RuleSystem *ruleSystem;

    Environment(unsigned int width, unsigned int height) {
        this->width = width;
        this->height = height;

        matrix = new Cell *[height];
        for (unsigned int i = 0; i < height; ++i) {
            matrix[i] = new Cell[width * 2];
        }

        neighbors = new unsigned short *[height];
        for (unsigned int i = 0; i < height; ++i) {
            neighbors[i] = new unsigned short[width];
        }
    }

    /**
     * Returns the number of living cells in the neighborhood (containing 6 neighbors).
     * @param row
     * @param col
     * @return
     */
    unsigned int get6Neighbors(unsigned int row, unsigned int col) {
        unsigned int realCol = getRealCol(row, col);
        unsigned int neighbor = 0;

        for (int i = -1; i <= 1; ++i) {
            for (int j = -2; j <= 2; ++j) {
                if (i != 0 && j != 0 && matrix[row + i][realCol + j].isValid()) {
                    try {
                        neighbor += matrix[row + i][realCol + j].getState();
                    } catch (std::exception &e) {}
                }
            }
        }

        return neighbor;
    }

    /**
     * Returns the number of living cells in the neighborhood (containing 8 neighbors).
     * @param row
     * @param col
     * @return
     */
    unsigned int get8Neighbors(unsigned int row, unsigned int col) {
        unsigned int realCol = getRealCol(row, col);
        unsigned int neighbor = 0;

        for (int i = -2; i <= 2; ++i) {
            for (int j = -2; j <= 2; ++j) {
                if (i != 0 && j != 0 && abs(i) != 2 && abs(j) != 2
                    && matrix[row + i][realCol + j].isValid()) {

                    try {
                        neighbor += matrix[row + i][realCol + j].getState();
                    } catch (std::exception &e) {}
                }
            }
        }

        return neighbor;
    }

    /**
     * Returns the number of living cells in the neighborhood (containing 12 neighbors).
     * @param row
     * @param col
     * @return
     */
    unsigned int get12Neighbors(unsigned int row, unsigned int col) {
        unsigned int realCol = getRealCol(row, col);
        unsigned int neighbor = 0;

        for (int i = -2; i <= 2; ++i) {
            for (int j = -3; j <= 3; ++j) {
                if (i != 0 && j != 0 && abs(i) != 2 && abs(j) != 2
                    && matrix[row + i][realCol + j].isValid()) {

                    try {
                        neighbor += matrix[row + i][realCol + j].getState();
                    } catch (std::exception &e) {}
                }
            }
        }

        return neighbor;
    }

    void judgeState(unsigned int row, unsigned int col) {
        switch (ruleSystem->judge(neighbors[row][col])) {
            case 's':
                break;
            case 'b':
                matrix[row][getRealCol(row, col)].live();
                break;
            case 'd':
                matrix[row][getRealCol(row, col)].kill();
                break;
        }
    }

    void refreshNeighborMatrix() {
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                neighbors[i][j] = get12Neighbors(i, j);
            }
        }
    }

    /**
     * Every row has <code>col<code> many hexagonal cells, but in the matrix every row, has 2*<code>col<code> cells,
     * half of which is not valid. This function returns the actual position of the col-th cell.
     * @param row
     * @param col
     * @return
     */
    static unsigned int getRealCol(unsigned int row, unsigned int col) {
        return col == 0 ? (row % 2 == 0 ? 1 : 0) : (row % 2 == 0 ? col*2-1 : col*2);
    }

public:

    Environment() = default;

    Environment(unsigned int width, unsigned int height, int AR) : Environment(width, height) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);

        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width * 2; ++j) {

                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
                    matrix[i][j].invalidate();
                } else {

                    if (dis(gen) < AR) {
                        matrix[i][j].live();
                    } else {
                        matrix[i][j].kill();
                    }

                }

            }
        }
    }

    ~Environment() {
        for (unsigned int i = 0; i < height; ++i) {
            delete[] matrix[i];
        }
    }

    /**
     * Evolves the environment(changes the <code>matrix<code>), increases the generation number.
     */
    void nextStep() {
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                judgeState(i, j);
            }
        }
    }

    void setRuleSystem(RuleSystem *rs) {
        this->ruleSystem = rs;
    }

    Cell **getMatrix() {
        return matrix;
    }

    unsigned int getWidth() {
        return width;
    }

    unsigned int getHeight() {
        return height;
    }
};

#endif //GOL_HEX_ENVIRONMENT_H
