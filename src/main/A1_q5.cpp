#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q5; see 题面.pdf.
namespace aim::q5 {


// BEGIN IMPLEMENTATION
// aim-cpp-cw
int count_adjacent_obstacles(const std::vector<std::string>& grid, int row, int col) {
    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());
    int count = 0;

    if (row > 0 && grid[row - 1][col] == '#') {
        ++count;
    }
    if (row + 1 < rows && grid[row + 1][col] == '#') {
        ++count;
    }
    if (col > 0 && grid[row][col - 1] == '#') {
        ++count;
    }
    if (col + 1 < cols && grid[row][col + 1] == '#') {
        ++count;
    }

    return count;
}

std::vector<std::vector<int>> risk(const std::vector<std::string>& grid) {
    if (grid.empty()) {
        return {};
    }

    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());
    if (cols == 0) {
        throw std::invalid_argument("grid has zero columns");
    }

    for (const std::string& row : grid) {
        if (static_cast<int>(row.size()) != cols) {
            throw std::invalid_argument("grid rows differ in length");
        }
        for (char cell : row) {
            if (cell != '.' && cell != '#') {
                throw std::invalid_argument("grid contains an invalid character");
            }
        }
    }

    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0));

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (grid[row][col] == '#') {
                result[row][col] = -1;
                continue;
            }
            result[row][col] = count_adjacent_obstacles(grid, row, col);
        }
    }

    return result;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q5;
int main() {
    try {
        { CHECK((risk({".#",".."})==std::vector<std::vector<int>>{{1,-1},{0,1}})); }
        { CHECK(risk({}).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
