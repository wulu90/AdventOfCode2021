#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream ifs{"input\\input-9"};
    vector<vector<int8_t>> heightmap;

    int row = 0;
    int col = 0;

    string line;
    char c;
    while (getline(ifs, line))
    {
        col = line.size();
        istringstream iss{line};
        vector<int8_t> row_vec;
        while (iss >> c)
        {
            row_vec.emplace_back(c - '0');
        }
        heightmap.emplace_back(row_vec);
    }

    vector<int8_t> low_points;
    for (int i = 0; i < heightmap.size(); i++)
    {
        for (int j = 0; j < col; j++)
        {

            char up_compare = 0;
            char down_compare = 0;
            char left_compare = 0;
            char right_compare = 0;

            up_compare = i == 0 ? 10 : heightmap[i - 1][j];
            down_compare = i == heightmap.size() - 1 ? 10 : heightmap[i + 1][j];
            left_compare = j == 0 ? 10 : heightmap[i][j - 1];
            right_compare = j == col - 1 ? 10 : heightmap[i][j + 1];

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
