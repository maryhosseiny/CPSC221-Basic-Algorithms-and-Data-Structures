#include "HexCell.h"

#include <cmath>

HexCell::HexCell(int Q, int R) {
    /**
     * @todo Your code here!
     */
    q = Q;
    r = R;
    for (int i=0; i<6; i++) {
        neighbours[i] = nullptr;
        links[i] = nullptr;
    }
    path_dist_from_start = 0;
}

void HexCell::link(HexCell* cell) {
    /**
     * @todo Your code here!
     */
    if (cell == nullptr) {
        return;
    }
    for (int i=0; i<6; i++) {
        if (distance(cell) == 1) {
            int direction = 0;
            if (cell->q == this->q) {
                if (cell->r > this->r) {
                    direction = 3;
                }
            } else if (cell->q > this->q) {
                if (cell->r < this->r) {
                    direction = 1;
                } else {
                    direction = 2;
                }
            } else {
                if (cell->r > this->r) {
                    direction = 4;
                } else {
                    direction = 5;
                }
            }
            links[direction] = cell;
            direction += 3;
            if (direction > 6) {
                direction -= 6;
            }
            cell->links[direction] = this;
        }
    }
}

int HexCell::get_neighbour_side(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    for (int i=0; i<6; i++) {
        if (links[i] == cell) {
            return i;
        }
    }
    return -1;
}

bool HexCell::is_linked(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (cell==nullptr) {
        return false;
    }
    for (int i=0; i<6; i++) {
        if (links[i] == cell) {
            return true;
        }
    }
    return false;
}

int HexCell::distance(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (cell == nullptr){
        return -1;
    } else {
        int base = abs(this->r - cell->r);
        int height = abs(this->q - cell->q);
        int otherside = abs(-this->q -this->r + cell->q + cell->r);
        return std::max(std::max(base, height), otherside);
    }
}

bool HexCell::is_edge() const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    for (int i=0; i<6; i++) {
        if (neighbours[i] == nullptr) {
            return true;
        }
    }
    return false;
}