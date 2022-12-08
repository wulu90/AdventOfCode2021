#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<size_t> can_move_east(const std::vector<char>& row) {
    std::vector<size_t> result;

    for (size_t i = 0; i < row.size() - 1; i++) {
        if (row[i] == '>' && row[i + 1] == '.') {
            result.push_back(i);
        }
    }

    if (row[row.size() - 1] == '>' && row[0] == '.') {
        result.push_back(row.size() - 1);
    }
    return result;
}

std::vector<size_t> can_move_south(const std::vector<std::vector<char>>& cucus, size_t col_inx) {
    std::vector<size_t> result;

    for (size_t i = 0; i < cucus.size() - 1; i++) {
        if (cucus[i][col_inx] == 'v' && cucus[i + 1][col_inx] == '.') {
            result.push_back(i);
        }
    }

    if (cucus[cucus.size() - 1][col_inx] == 'v' && cucus[0][col_inx] == '.') {
        result.push_back(cucus.size() - 1);
    }
    return result;
}

std::vector<std::pair<size_t, size_t>> move_east(const std::vector<std::vector<char>>& cucus) {
    std::vector<std::pair<size_t, size_t>> result;

    for (size_t i = 0; i < cucus.size(); i++) {
        auto r = can_move_east(cucus[i]);
        for (auto j : r) {
            result.push_back({i, j});
        }
    }

    return result;
}

std::vector<std::pair<size_t, size_t>> move_south(const std::vector<std::vector<char>>& cucus) {
    std::vector<std::pair<size_t, size_t>> result;

    for (size_t i = 0; i < cucus[0].size(); i++) {
        auto r = can_move_south(cucus, i);
        for (auto j : r) {
            result.push_back({j, i});
        }
    }

    return result;
}

void printcucus(const std::vector<std::vector<char>>& cucus) {
    for (auto row : cucus) {
        for (auto c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void move(std::vector<std::vector<char>>& cucus) {
    size_t row_num = cucus.size();
    size_t col_num = cucus[0].size();

    auto east  = move_east(cucus);
    auto south = move_south(cucus);

    int step = 0;

    while (!east.empty() || !south.empty()) {
        step += 1;
        for (auto c : east) {
            if (c.second != col_num - 1) {
                cucus[c.first][c.second + 1] = '>';
                cucus[c.first][c.second]     = '.';
            } else {
                cucus[c.first][0]        = '>';
                cucus[c.first][c.second] = '.';
            }
        }

        south = move_south(cucus);

        for (auto c : south) {
            if (c.first != row_num - 1) {
                cucus[c.first + 1][c.second] = 'v';
                cucus[c.first][c.second]     = '.';
            } else {
                cucus[0][c.second]       = 'v';
                cucus[c.first][c.second] = '.';
            }
        }

        // std::cout << "step " << step << std::endl;
        // printcucus(cucus);
        east  = move_east(cucus);
        south = move_south(cucus);
    }

    std::cout << step + 1 << std::endl;
}

int main() {
    std::ifstream input("input/input-25");

    std::vector<std::vector<char>> cucumbers;
    std::string line;

    while (std::getline(input, line)) {
        std::vector<char> tmp(line.begin(), line.end());
        cucumbers.push_back(tmp);
    }

    move(cucumbers);
}