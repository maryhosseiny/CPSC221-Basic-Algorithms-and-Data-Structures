#include "HexBoard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

HexBoard::HexBoard(int radius)
{
    /**
     * @todo Your code here!
     */
    this->radius = radius;
    create_board();
    configure_cells();
}

void HexBoard::create_board()
{
    /**
     * @todo Your code here!
     */
    if (radius != 1) {
        radius -= 1;
        for (int q = -radius; q <= radius; q++) {
            for (int r = -radius; r <= radius; r++) {
                if (q + r <= radius && q + r >= -radius) {
                    cells[{q, r}] = new HexCell(q, r);
                }
            }
        }
        radius = radius + 1;
    } else {
        cells[{0, 0}] = new HexCell(0, 0);
        return;
    }
    
}

void HexBoard::configure_cells()
{
    if (radius != 1) {
        radius -= 1;
        for (int q = -radius; q <= radius; q++) {
            for (int r = -radius; r <= radius; r++) {
                if (q + r <= radius && q + r >= -radius) {
                    vector<pair<int, int>> neigh_coords = get_neigh_coords({q, r});
                    for (int i=0; i<6; i++) {
                        if (cells.find(neigh_coords[i]) != cells.end()) {
                            if (cells[{q, r}]->neighbours[i] != cells[neigh_coords[i]]) {
                                cells[{q, r}]->neighbours[i] = cells[neigh_coords[i]];
                            }
                            int direction = i+3;
                            if (5 < direction) {
                                direction -= 6;
                            }
                            if (cells[neigh_coords[i]]->neighbours[direction] != cells[{q, r}]) {
                                cells[neigh_coords[i]]->neighbours[direction] = cells[{q, r}];
                            }
                            
                        }
                    }
                }
            }
        }
        radius = radius + 1;
    } 
    return;
    
}

void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob)
{
    /**
     * @todo Your code here!
     */
    map<pair<int, int>, bool> visited;
    Stack<pair<int, int>> stack_dfs;

    this->start_coord = start_coord;
    stack_dfs.push(start_coord);
    visited[start_coord] = true;

    while (!stack_dfs.isEmpty()) {
        pair<int, int> curr_cell_coor = stack_dfs.peek();
        HexCell* curr_cell = cells[curr_cell_coor];
        HexCell* neigh_cell = chooseNeighbour(curr_cell, visited, branch_prob);
        
        if (neigh_cell) {
            curr_cell->link(neigh_cell);
            neigh_cell->link(curr_cell);

            visited[{neigh_cell->q, neigh_cell->r}] = true;
            neigh_cell->path_dist_from_start = curr_cell->path_dist_from_start + 1;
                
            if (longest_path_dist < neigh_cell->path_dist_from_start) {
                longest_path_dist = neigh_cell->path_dist_from_start;
                
            }
            if (neigh_cell->is_edge() && neigh_cell->path_dist_from_start > cells[end_coord]->path_dist_from_start) {
                end_coord = {neigh_cell->q, neigh_cell->r};
            }
            stack_dfs.push({neigh_cell->q, neigh_cell->r});
        } else {
            stack_dfs.pop();
        }
    }
}

void HexBoard::solve_maze()
{
    /**
     * @todo Your code here!
     */
    Stack<pair <int, int>> visited;
    visited.push(end_coord);
    HexCell* cell = cells[end_coord];

    while (cell != cells[start_coord]) {
        for (int i = 0; i < 6; i++) {
            HexCell* linked = cell->links[i];
            if (linked != nullptr) {
                if (linked->path_dist_from_start == (cell->path_dist_from_start-1)) {
                    visited.push({linked->q, linked->r});
                    cell = linked;
                }
            }
        }
    }
    while (!visited.isEmpty()) {
        solution.push_back(visited.pop());
    }
}
