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
            int index = 0;
            if (cell->q == q) {
                if (cell->r > r) {
                    index = 3;
                }
            } else if (cell->q > q) {
                if (cell->r < r) {
                    index = 1;
                } else {
                    index = 2;
                }
            } else {
                if (cell->r > r) {
                    index = 4;
                } else {
                    index = 5;
                }
            }
            links[index] = cell;
            index += 3;
            if (index > 6) {
                index -= 6;
            }
            cell->links[index] = this;
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
    if (cell == nullptr) {
        return -1;
    }
    int q_dif = cell->q - q;
    int r_dif = cell->r - r;
    if ((q_dif > 0 && r_dif > 0)||(q_dif < 0 && r_dif < 0)) {
        return abs(q_dif) + abs(r_dif);
    }
    return std::max(abs(q_dif), abs(r_dif));
    
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