// Robot is given the knowledge of Grid Occupancy Mapping, current location, and
// the destination as illustrated below. Current robot’s location is at (3, 1),
// destination is at (4, 6), and the gray color represents occupied cells.
//     Write a solution class to search for a navigable path from current
//     location to the destination,
// and validate your solution against the illustrated sample in the main()
// function by printing out the path (a sequence of cells index) you found.
//           Note that the robot can only move to adjacent cells either
//           vertically or horizontally but not diagonally;
// and you could assume the dimension of input map will always be 7x7.
#include <iostream>
#include <vector>

struct Cell {
    int x = -1;
    int y = -1;
    Cell(){};
    Cell(int x, int y) : x(x), y(y) {}
    Cell(Cell const& cell) {
        x = cell.x;
        y = cell.y;
    }
};

class SearchPath {
private:
    bool found_path_{false};
    std::vector<Cell> path_result_;

public:
    std::vector<Cell> searchPath(std::vector<std::vector<int>>& map,
                                 Cell start,
                                 Cell end) {

        Cell cell = startDFS(map, start, end);


        return path_result_;
    }

    Cell startDFS(std::vector<std::vector<int>>& map, Cell start, Cell end) {
        Cell invalid_cell_(-1, -1);
        Cell error_cell(-1, -1);
        Cell current_cell = start;
        if (start.x >= map.size() || start.x < 0 || start.y >= map[0].size() ||
            start.y < 0 || end.x >= map.size() || end.x < 0 ||
            end.y >= map[0].size() || end.y < 0) {
            // std::cout << "Start or end out of bound" << '\n';
            current_cell = error_cell;
            return current_cell;
        }
        if (map[start.x][start.y] == 0) {
            // std::cout << "Obstacle at " << start.x << " " << start.y <<
            // "\n";
            current_cell = error_cell;
            return current_cell;
        }
        if (map[start.x][start.y] == 1) {
            // std::cout << "Visited at " << start.x << " " << start.y <<
            // "\n";
            current_cell = error_cell;
            return current_cell;
        }

        if (start.x == end.x && start.y == end.y) {
            std::cout << "Found goal at: " << start.x << " " << start.y << "\n";
            map[start.x][start.y] = 1;
            found_path_ = true;
            // if(found_path_)
            // path_result_.push_back(start);
            return current_cell;
        }

        if (map[start.x][start.y] == -1) {
            // std::cout << "Valid cell: " << start.x << " " << start.y << "\n";
            map[start.x][start.y] = 1;
        }

        start.y += 1;
        current_cell = startDFS(map, start, end);
        start.y += -1;

        start.x += -1;
        current_cell = startDFS(map, start, end);
        start.x += 1;

        start.y += -1;
        current_cell = startDFS(map, start, end);
        start.y += 1;

        start.x += 1;
        current_cell = startDFS(map, start, end);
        start.x += -1;

        if (current_cell.x != invalid_cell_.x &&
            current_cell.y != invalid_cell_.y && found_path_) {
            path_result_.push_back(current_cell);
        }

        return current_cell;
    }
};

int main() {
    // int map_row = 7;
    // int map_col = 7;
    int map_row = 3;
    int map_col = 3;

    // Cell start_pos(3, 1);
    // Cell goal_pos(4, 6);
    Cell start_pos(0, 0);
    Cell goal_pos(2, 2);

    // init an unknown map map_row x map_col with -1
    std::vector<std::vector<int>> map(map_row, std::vector<int>(map_col, -1));
    // 0 = obstacle
    // 1 = visited
    // map[2][3] = 0;
    // map[2][4] = 0;
    // map[3][3] = 0;
    // map[3][4] = 0;
    // map[4][3] = 0;
    // map[4][4] = 0;
    // map[1][1] = 0;
    // map[1][2] = 0;
    map[1][0] = 0;

    SearchPath search_obj;
    std::vector<Cell> path = search_obj.searchPath(map, start_pos, goal_pos);

    for (const auto& cell : path) {
        // if (cell.x == goal_pos.x && cell.y == goal_pos.y) start_print = true;
        // if (cell.x == invalid_cell.x && cell.y == invalid_cell.y ||
        //     !start_print)
        //     continue;
        std::cout << "Cell: " << cell.x << ", " << cell.y << '\n';
    }

    std::cout << '\n';

    return 0;
};