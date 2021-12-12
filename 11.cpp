#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <array>

using namespace std;
void part1()
{
    ifstream ifs{"input\\input-10"};
    string line;
    char c;
    vector<vector<int8_t>> energy_levels;

    while (getline(ifs, line))
    {
        vector<int8_t> eline;
        for (auto &c : line)
        {
            eline.emplace_back(c - '0');
        }
        energy_levels.emplace_back(eline);
    }

    int flash_count = 0;
    array<array<int8_t, 10>, 10> flashed;
    flashed.fill({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    int8_t dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}; // row,col
    deque<pair<int8_t, int8_t>> flash_coord;

    for (int step = 0; step < 100; step++)
    {
        flashed.fill({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
        flash_coord.clear();

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                energy_levels[i][j] += 1;
                if (energy_levels[i][j] > 9)
                {
                    flash_coord.emplace_back(pair(i, j));
                }
            }
        }

        while (!flash_coord.empty())
        {
            int8_t i = flash_coord.front().first;
            int8_t j = flash_coord.front().second;

            if (flashed[i][j] == 1)
            {
                flash_coord.pop_front();
                continue;
            }

            flashed[i][j] = 1;
            flash_count += 1;
            flash_coord.pop_front();
            energy_levels[i][j] = 0;

            for (int k = 0; k < 8; k++)
            {
                int8_t adj_i = i + dir[k][0];
                int8_t adj_j = j + dir[k][1];

                // check if not edge or corner;
                if (adj_i < 0 || adj_j < 0 || adj_i > 9 || adj_j > 9)
                    continue;

                if (flashed[adj_i][adj_j] == 0) // not flashed
                {
                    energy_levels[adj_i][adj_j] += 1;
                    if (energy_levels[adj_i][adj_j] > 9)
                    {
                        flash_coord.emplace_back(pair(adj_i, adj_j));
                    }
                }
            }
        }
    }

    cout << flash_count << endl;
}

void part2()
{
    ifstream ifs{"input\\input-10"};
    string line;
    char c;
    vector<vector<int8_t>> energy_levels;

    while (getline(ifs, line))
    {
        vector<int8_t> eline;
        for (auto &c : line)
        {
            eline.emplace_back(c - '0');
        }
        energy_levels.emplace_back(eline);
    }

    int flash_count = 0;
    array<array<int8_t, 10>, 10> flashed;
    flashed.fill({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    int8_t dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}; // row,col
    int8_t step_flash_count = 0;
    int step = 0;
    deque<pair<int8_t, int8_t>> flash_coord;

    while (true)
    {
        flashed.fill({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
        flash_coord.clear();
        step_flash_count = 0;
        step += 1;

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                energy_levels[i][j] += 1;
                if (energy_levels[i][j] > 9)
                {
                    flash_coord.emplace_back(pair(i, j));
                }
            }
        }

        while (!flash_coord.empty())
        {
            int8_t i = flash_coord.front().first;
            int8_t j = flash_coord.front().second;

            if (flashed[i][j] == 1)
            {
                flash_coord.pop_front();
                continue;
            }

            flashed[i][j] = 1;
            flash_count += 1;
            step_flash_count += 1;
            flash_coord.pop_front();
            energy_levels[i][j] = 0;

            for (int k = 0; k < 8; k++)
            {
                int8_t adj_i = i + dir[k][0];
                int8_t adj_j = j + dir[k][1];

                // check if not edge or corner;
                if (adj_i < 0 || adj_j < 0 || adj_i > 9 || adj_j > 9)
                    continue;

                if (flashed[adj_i][adj_j] == 0) // not flashed
                {
                    energy_levels[adj_i][adj_j] += 1;
                    if (energy_levels[adj_i][adj_j] > 9)
                    {
                        flash_coord.emplace_back(pair(adj_i, adj_j));
                    }
                }
            }
        }

        if (step_flash_count == 100)
        {
            break;
        }
    }

    cout << "all flash in after step:" << step << endl;
}

int main()
{
    part1();
    part2();
}
