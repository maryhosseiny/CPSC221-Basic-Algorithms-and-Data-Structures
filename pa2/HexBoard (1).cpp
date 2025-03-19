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
    if (radius == 1)
    {
        cells[{0, 0}] = new HexCell(0, 0);
        return;
    }
    radius -= 1;
    for (int q = -radius; q <= radius; q++) {
        for (int r = -radius; r <= radius; r++) {
            if (q + r <= radius && q + r >= -radius) {
                cells[{q, r}] = new HexCell(q, r);
            }
        }
    }
    radius += 1;
}

void HexBoard::configure_cells()
{
    if (radius == 1)
    {
        return;
    }
    radius -= 1;
    vector<pair<int, int>> neigh_coors;
    for (int q = -radius; q <= radius; q++) {
        for (int r = -radius; r <= radius; r++) {
            if (q + r <= radius && q + r >= -radius) {
                neigh_coors = get_neigh_coords({q, r});
                for (int i=0; i<6; i++) {
                    if (cells.find(neigh_coors[i]) == cells.end()) {
                    // not found
                    } else {
                        //cout<<q<<", "<<r<<"\n";
                        if (cells[{q, r}]->neighbours[i] != cells[neigh_coors[i]]) {
                            cells[{q, r}]->neighbours[i] = cells[neigh_coors[i]];
                        }
                        int index = i+3;
                        if (index > 5) {
                            index -= 6;
                        }
                        if (cells[neigh_coors[i]]->neighbours[index] != cells[{q, r}]) {
                            cells[neigh_coors[i]]->neighbours[index] = cells[{q, r}];
                        }
                        
                    }
                }
            }
        }
    }
    radius += 1;
}

void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob)
{
    /**
     * @todo Your code here!
     */
    map<pair<int, int>, bool> visited;
    Stack<pair<int, int>> stack;
    this->start_coord = start_coord;
    stack.push(start_coord);
    visited[start_coord] = true;
    pair<int, int> curr_cell_coor;
    HexCell* curr_cell;
    HexCell* neigh_cell;
    pair<int, int> neigh_coor;
    while (!stack.isEmpty())
    {
        curr_cell_coor = stack.peek();
        curr_cell = cells[curr_cell_coor];
        neigh_cell = chooseNeighbour(curr_cell, visited, branch_prob);
        
        if (neigh_cell != nullptr) {
            curr_cell->link(neigh_cell);
            neigh_cell->link(curr_cell);
            neigh_coor = {neigh_cell->q, neigh_cell->r};
            // cout << "a" << "\n";
            // cout << curr_cell->q<<", "<<curr_cell->r << "\n";
            // cout << neigh_cell->q<<", " << neigh_cell->r <<"\n";
            visited[neigh_coor] = true;
            neigh_cell->path_dist_from_start = curr_cell->path_dist_from_start + 1;
            // cout << "b" << "\n";
            // cout << neigh_cell->path_dist_from_start<<", " << longest_path_dist<<"\n";
                
            if (neigh_cell->path_dist_from_start > longest_path_dist) {
                longest_path_dist = neigh_cell->path_dist_from_start;
                
            }
            if (neigh_cell->is_edge() && neigh_cell->path_dist_from_start > cells[end_coord]->path_dist_from_start) {
                end_coord = neigh_coor;
            }
            stack.push(neigh_coor);
        } else {
            stack.pop();
        }
    }
}

void HexBoard::solve_maze()
{
    /**
     * @todo Your code here!
     */
    map<pair<int, int>, bool> visited;
    bool result = helper(start_coord, visited, false);
}

bool HexBoard::helper(pair<int, int> cur, map<pair<int, int>, bool> visited, bool found) {
    //cout << cur.first << ", " << cur.second << "\n";
    solution.push_back(cur);
    if (cur == end_coord) {
        found = true;
        return found;
    }
    visited[cur] = true;
    vector<pair<int, int>> neighbors = get_neigh_coords(cur);
    for (const auto& neighbor : neighbors) {
        if (cells.find(neighbor) == cells.end()) {
            continue;
        }
        if (cells[cur]->is_linked(cells[neighbor])==false) {
            continue;
        }
        if (visited.count(neighbor) == true) {
            continue;
        }
        found = helper(neighbor, visited, found);
        if (found) {
            return found;
        }
    }
    solution.pop_back();
    return false;
}