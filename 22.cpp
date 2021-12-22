#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>
#include <tuple>

using namespace std;

class cuboid
{
public:
    bool turn;
    bool greater50;
    int32_t xmin;
    int32_t xmax;
    int32_t ymin;
    int32_t ymax;
    int32_t zmin;
    int32_t zmax;

    cuboid(const string &str)
    {
        greater50 = false;
        if (str.starts_with("on"))
        {
            turn = true;
        }
        else if (str.starts_with("off"))
        {
            turn = false;
        }

        auto x_equal = str.find('=');
        auto x_dot = str.find("..");
        auto x_comma = str.find(',');
        xmin = stoi(str.substr(x_equal + 1, x_dot - x_equal - 1));
        xmax = stoi(str.substr(x_dot + 2, x_comma - x_equal - 2));

        auto y_equal = str.find('=', x_comma + 1);
        auto y_dot = str.find("..", x_comma + 1);
        auto y_comma = str.find(',', x_comma + 1);
        ymin = stoi(str.substr(y_equal + 1, y_dot - y_equal - 1));
        ymax = stoi(str.substr(y_dot + 2, y_comma - y_equal - 2));

        auto z_equal = str.find('=', y_comma + 1);
        auto z_dot = str.find("..", y_comma + 1);
        auto z_comma = str.find(',', y_comma + 1);
        zmin = stoi(str.substr(z_equal + 1, z_dot - z_equal - 1));
        zmax = stoi(str.substr(z_dot + 2, z_comma - z_equal - 2));

        if (abs(xmin) > 50 || abs(xmax) > 50 || abs(ymin) > 50 || abs(ymax) > 50 || abs(zmin) > 50 || abs(zmax) > 50)
        {
            greater50 = true;
        }
    }

    vector<tuple<int32_t, int32_t, int32_t>> getcube()
    {
        vector<tuple<int32_t, int32_t, int32_t>> r;
        for (int32_t x = xmin; x <= xmax; x++)
        {
            for (int32_t y = ymin; y <= ymax; y++)
            {
                for (int32_t z = zmin; z <= zmax; z++)
                {
                    r.push_back({x, y, z});
                }
            }
        }
        return r;
    }
};

void part1()
{
    ifstream ifs{"input\\input-22"};
    string line;

    vector<cuboid> cuboids;
    while (getline(ifs, line))
    {
        cuboids.push_back(line);
    }

    set<tuple<int32_t, int32_t, int32_t>> cube_on;
    for (auto &cuboid : cuboids)
    {
        if (cuboid.turn && !cuboid.greater50)
        {
            for (auto &t : cuboid.getcube())
            {
                cube_on.insert(t);
            }
        }
        if (!cuboid.turn && !cuboid.greater50)
        {
            for (auto &t : cuboid.getcube())
            {
                cube_on.erase(t);
            }
        }
    }

    cout << cube_on.size() << endl;
}

int main()
{
    part1();
}