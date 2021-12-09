#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void part1()
{
    ifstream ifs{"input\\input-9"};
    vector<vector<int8_t>> heightmap;

    string line;
    char c;

    getline(ifs, line);
    int col = line.size();
    vector<int8_t> all9(col + 2, 9);
    heightmap.emplace_back(all9);

    ifs.clear();
    ifs.seekg(0);
    while (getline(ifs, line))
    {
        istringstream iss{line};
        vector<int8_t> row_vec;
        row_vec.reserve(col + 2);
        row_vec.emplace_back(9);
        while (iss >> c)
        {
            row_vec.emplace_back(c - '0');
        }
        row_vec.emplace_back(9);
        heightmap.emplace_back(row_vec);
    }

    int row = heightmap.size() - 1;

    heightmap.emplace_back(all9);

    // 99999999999999
    // 9            9
    // 9            9
    // 9            9
    // 9            9
    // 9            9
    // 99999999999999

    vector<int8_t> low_points;
    for (int i = 1; i < row + 1; i++)
    {
        for (int j = 1; j < col + 1; j++)
        {
            char up_compare = heightmap[i - 1][j];
            char down_compare = heightmap[i + 1][j];
            char left_compare = heightmap[i][j - 1];
            char right_compare = heightmap[i][j + 1];

            char height = heightmap[i][j];
            if (height < up_compare && height < down_compare && height < left_compare && height < right_compare)
            {
                low_points.emplace_back(height);
            }
        }
    }

    int risk_level = 0;
    for (auto c : low_points)
    {
        risk_level += c;
    }
    risk_level += low_points.size();
    cout << risk_level << endl;
}

void part2()
{
    ifstream ifs{"input\\input-9"};
    vector<vector<int8_t>> heightmap;

    string line;
    char c;

    getline(ifs, line);
    int col = line.size();
    vector<int8_t> all9(col + 2, 9);
    heightmap.emplace_back(all9);

    ifs.clear();
    ifs.seekg(0);
    while (getline(ifs, line))
    {
        istringstream iss{line};
        vector<int8_t> row_vec;
        row_vec.reserve(col + 2);
        row_vec.emplace_back(9);
        while (iss >> c)
        {
            row_vec.emplace_back(c - '0');
        }
        row_vec.emplace_back(9);
        heightmap.emplace_back(row_vec);
    }

    int row = heightmap.size() - 1;

    heightmap.emplace_back(all9);

    // 99999999999999
    // 9            9
    // 9            9
    // 9            9
    // 9            9
    // 9            9
    // 99999999999999

    //vector<int8_t> low_points;
    set<pair<int, int>> low_point_locations;
    for (int i = 1; i < row + 1; i++)
    {
        for (int j = 1; j < col + 1; j++)
        {
            char up_compare = heightmap[i - 1][j];
            char down_compare = heightmap[i + 1][j];
            char left_compare = heightmap[i][j - 1];
            char right_compare = heightmap[i][j + 1];

            char height = heightmap[i][j];
            if (height < up_compare && height < down_compare && height < left_compare && height < right_compare)
            {
                //low_points.emplace_back(height);
                low_point_locations.insert({i, j});
            }
        }
    }

    vector<int> basin_sizes;

    deque<pair<int, int>> searchs;
    set<pair<int, int>> basin_coords;

    int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (auto &low_p : low_point_locations)
    {
        searchs.clear();
        basin_coords.clear();

        basin_coords.insert({low_p.first, low_p.second});
        searchs.push_back({low_p.first, low_p.second});

        while (!searchs.empty())
        {
            auto sr = searchs.front();
            searchs.pop_front();
            for (int i = 0; i < 4; i++)
            {
                int r = sr.first + dir[i][0];
                int c = sr.second + dir[i][1];
                if (basin_coords.find({r, c}) == basin_coords.end() && heightmap[r][c] != 9)
                {
                    basin_coords.insert({r, c});
                    searchs.push_back({r, c});
                }
            }
        }

        basin_sizes.emplace_back(basin_coords.size());
    }

    sort(basin_sizes.begin(), basin_sizes.end());
    cout << (*basin_sizes.rbegin()) * (*(basin_sizes.rbegin() + 1)) * (*(basin_sizes.rbegin() + 2)) << endl;
}

int main()
{
    part1();
    part2();
}
