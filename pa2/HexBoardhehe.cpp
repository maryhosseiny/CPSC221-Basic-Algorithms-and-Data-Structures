#include "HexBoard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

HexBoard::HexBoard(int radius) {
    /**
     * @todo Your code here!
     */
     this->radius = radius;
     create_board();
     configure_cells();
}

void HexBoard::create_board() {
    /**
     * @todo Your code here!
     */
    if (radius != 1) {
        radius -= 1;
        for (int q = -radius ; q <= radius; q++) {
            for (int r = -radius; r <= radius; r++) {
                if (q + r <= radius && q + r >= -radius) {
                    cells[make_pair(q, r)] = new HexCell(q, r);
                }
            }
        }
        radius += 1;
    } else {
        cells[{0, 0}] = new HexCell(0, 0);
        return;
    }
    
}

void HexBoard::configure_cells() {
    /**
     * @todo Your code here!
     */
    if (radius != 1) {
        radius = radius - 1;
        for (int q = -radius; q <= radius; q++) {
            for (int r = -radius; r <= radius; r++) {
                if (q + r <= radius && q + r >= -radius) {
                    vector<pair<int, int>> neigh_coords = get_neigh_coords({q, r});
                    for (int i=0; i<6; i++) {
                        if (cells.find(neigh_coords[i]) == cells.end()) {
                            return;
                        } else {
                            if (cells[{q, r}]->neighbours[i] != cells[neigh_coords[i]]) {
                                cells[{q, r}]->neighbours[i] = cells[neigh_coords[i]];
                            }
                            int index = i+3;
                            if (index > 5) {
                                index -= 6;
                            }
                            if (cells[neigh_coords[i]]->neighbours[index] != cells[{q, r}]) {
                                cells[neigh_coords[i]]->neighbours[index] = cells[{q, r}];
                            }
                            
                        }
                    }
                }
            }
        }
        radius += 1;
    } 
    return;

}

void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob) {
    /**
     * @todo Your code here!
     */
    Stack<pair<int, int>> dfs_stack;
    map<pair<int, int>, bool> visited;
    this->start_coord = start_coord;
    dfs_stack.push(start_coord);
    visited[start_coord] = true;

    while (!dfs_stack.isEmpty()) {
        pair<int, int> curr_cord = dfs_stack.peek();
        HexCell* curr_cell = cells[curr_cord];

        // if (curr_cell->is_edge()) {
        //     longest_path_dist = std::max(longest_path_dist, curr_cell->path_dist_from_start); 
        // }

        HexCell* neigh_cell = chooseNeighbour(curr_cell, visited, branch_prob); 

        if (neigh_cell != nullptr) {
            curr_cell->link(neigh_cell);
            neigh_cell->link(curr_cell);
            visited[make_pair(neigh_cell->q, neigh_cell->r)] = true;
            neigh_cell->path_dist_from_start = curr_cell->path_dist_from_start + 1;
            if (neigh_cell->is_edge()) {
                longest_path_dist = std::max(longest_path_dist, neigh_cell->path_dist_from_start);
            }

            // // Step 2div: Update the end coordinate only if its path distance to start is strictly greater
            // if (neigh_cell->path_dist_from_start > this->longest_path_dist) {
            //     end_coord = make_pair(neigh_cell->q, neigh_cell->r);
            // }
            if (neigh_cell->is_edge() && neigh_cell->path_dist_from_start > cells[end_coord]->path_dist_from_start) {
                end_coord = make_pair(neigh_cell->q, neigh_cell->r);
            }
            dfs_stack.push(make_pair(neigh_cell->q, neigh_cell->r));
        } else {
            dfs_stack.pop();
        }
    }
}

void HexBoard::solve_maze() {
    /**
     * @todo Your code here!
     */
    // solution.clear();
    // HexCell* curr_cell = cells.at(start_coord);
    // solution.push_back(start_coord);

    // while (curr_cell->q != end_coord.first || curr_cell->r != end_coord.second) {
    //     HexCell* next_cell = nullptr;
    //     int min_distance = INT_MAX;

    //     for (HexCell* neigh_cell : curr_cell->neighbours) {
    //         if (neigh_cell && neigh_cell->path_distance < min_distance) {
    //             next_cell = neigh_cell;
    //             min_distance = neigh_cell->path_distance;
    //         }
    //     }

    //     if (next_cell) {
    //         solution.push_back({next_cell->q, next_cell->r});
    //         curr_cell = next_cell;
    //     }
    // }

    // solution.push_back(end_coord);
    // map<pair<int, int>, bool> visited;
    // bool result = helper(start_coord, visited, false);
}

// bool HexBoard::helper(pair<int, int> cur, map<pair<int, int>, bool> visited, bool found) {
//     //cout << cur.first << ", " << cur.second << "\n";
//     solution.push_back(cur);
//     if (cur == end_coord) {
//         found = true;
//         return found;
//     }
//     visited[cur] = true;
//     vector<pair<int, int>> neighbors = get_neigh_coords(cur);
//     for (const auto& neighbor : neighbors) {
//         if (cells.find(neighbor) == cells.end()) {
//             continue;
//         }
//         if (cells[cur]->is_linked(cells[neighbor])==false) {
//             continue;
//         }
//         if (visited.count(neighbor) == true) {
//             continue;
//         }
//         found = helper(neighbor, visited, found);
//         if (found) {
//             return found;
//         }
//     }
//     solution.pop_back();
//     return false;
// }