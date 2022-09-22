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

struct Point {
    int x_;
    int y_;
    Point(int x, int y) : x_(x), y_(y) {}
};

class Solution {
    private:
        std::vector<Point> path_result_;

    public:
        std::vector<Point> searchPath(std::vector<std::vector<int>>& map,
                                      Point start,
                                      Point end) {
            // std::vector<Point> path_result;

            // check if out of bound
            if (start.x_ >= map.size() || start.x_ < 0 ||
                start.y_ >= map[0].size() || start.y_ < 0 ||
                end.x_ >= map.size() || end.x_ < 0 || end.y_ >= map[0].size() ||
                end.y_ < 0) {
                std::cout << "Start or end out of bound" << '\n';
                return path_result_;
            }

            startDFS(map, start, end);

            return path_result_;
    }

    void startDFS(std::vector<std::vector<int>>& map, Point start, Point end) {
        if (start.x_ >= map.size() || start.x_ < 0 ||
            start.y_ >= map[0].size() || start.y_ < 0 || end.x_ >= map.size() ||
            end.x_ < 0 || end.y_ >= map[0].size() || end.y_ < 0) {
            // std::cout << "Start or end out of bound" << '\n';
            return;
        }
        if(map[start.x_][start.y_] == 0)
        {
            // std::cout << "Obstacle at " << start.x_ << " " << start.y_ << "\n";
            return;
        }
        if (map[start.x_][start.y_] == 1) {
            // std::cout << "Visited at " << start.x_ << " " << start.y_ << "\n";
            return;
        }


        if (start.x_ == end.x_ && start.y_ == end.y_) {

            std::cout << "Found path at: " << start.x_ << " " << start.y_ << "\n";
            map[start.x_][start.y_] = 1;
            return;
        }

        if (map[start.x_][start.y_] == -1) {
            std::cout << "Valid cell: " << start.x_ << " " << start.y_ << "\n";
            map[start.x_][start.y_] = 1;
            path_result_.push_back(start);
        }

        start.y_ += 1;
        startDFS(map, start, end);
        start.y_ += -1;

        start.x_ += -1;
        startDFS(map, start, end);
        start.x_ += 1;

        start.y_ += -1;
        startDFS(map, start, end);
        start.y_ += 1;

        start.x_ += 1;
        startDFS(map, start, end);
        start.x_ += -1;

    }
};

int main() {
    // int map_row = 7;
    // int map_col = 7;
    int map_row = 3;
    int map_col = 3;

    // Point start_pos(3, 1);
    // Point goal_pos(4, 6);
    Point start_pos(0, 0);
    Point goal_pos(2, 2);

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
    map[1][1] = 0;
    map[1][2] = 0;

    Solution solution;
    std::vector<Point> path = solution.searchPath(
            map, start_pos, goal_pos);

    for(const auto& c : path)
    {
        std::cout << "Path: " << c.x_ << ", " << c.y_ << " ";
    }

std::cout << '\n';

    return 0;
};