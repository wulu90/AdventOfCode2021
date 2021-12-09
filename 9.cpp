#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

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

int main()
{
    part1();
}
