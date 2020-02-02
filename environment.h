//
// Created by hidie on 2020. 02. 02..
//

#ifndef GOL_HEX_ENVIRONMENT_H
#define GOL_HEX_ENVIRONMENT_H

#include <random>
#include "cell.h"

class Environment {

private:

    Cell **matrix = nullptr;
    unsigned int width;
    unsigned int height;

    int getRealCol(int &row, int &col) {
        //TODO
    }

public:

    Environment() = default;

    Environment(unsigned int width, unsigned int height) {
        this->width = width;
        this->height = height;
        matrix = new Cell *[height];

        for (unsigned int i = 0; i < height; ++i) {
            matrix[i] = new Cell[width * 2];
        }
    }

    Environment(unsigned int width, unsigned int height, int AR) {
        this->width = width;
        this->height = height;
        matrix = new Cell *[height];

        for (unsigned int i = 0; i < height; ++i) {
            matrix[i] = new Cell[width * 2];
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);

        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width * 2; ++j) {

                if ((i%2 == 0 && j%2 == 0) || (i%2 != 0 && j%2 != 0)) {
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

    int get6Neighbors(int &row, int &col) {
        int realCol = getRealCol(row, col);
        int neighbors = 0;

        for(int i = -1; i <= 1; ++i) {
            for(int j = -2; j <= 2; ++j) {
                if(i != 0 && j != 0 && matrix[row+i][realCol+j].isValid()) {
                    try {
                        neighbors += matrix[row+i][realCol+j].getState();
                    } catch (std::exception &e) {}
                }
            }
        }

        return neighbors;
    }

    int get8Neighbors(int &row, int &col) {
        int realCol = getRealCol(row, col);
        int neighbors = 0;

        for(int i = -2; i <= 2; ++i) {
            for(int j = -2; j <= 2; ++j) {
                if(i != 0 && j != 0 && abs(i) != 2 && abs(j) != 2
                   && matrix[row+i][realCol+j].isValid()) {

                    try {
                        neighbors += matrix[row+i][realCol+j].getState();
                    } catch (std::exception &e) {}
                }
            }
        }

        return neighbors;
    }

    int get12Neighbors(int &row, int &col) {
        //TODO
    }
};

#endif //GOL_HEX_ENVIRONMENT_H
