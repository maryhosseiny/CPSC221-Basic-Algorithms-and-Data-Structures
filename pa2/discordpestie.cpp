
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
            
            visited[neigh_coor] = true;
            neigh_cell->path_dist_from_start = curr_cell->path_dist_from_start + 1;
              
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