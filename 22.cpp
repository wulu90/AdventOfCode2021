#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>
#include <tuple>
#include <algorithm>

using namespace std;

class cuboid
{
public:
    bool turn;
    int64_t xmin;
    int64_t xmax;
    int64_t ymin;
    int64_t ymax;
    int64_t zmin;
    int64_t zmax;

    cuboid() {}

    cuboid(const string &str)
    {
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
    }

    cuboid(bool on, int64_t x1, int64_t x2, int64_t y1, int64_t y2, int64_t z1, int64_t z2)
        : turn(on), xmin(x1), xmax(x2), ymin(y1), ymax(y2), zmin(z1), zmax(z2)
    {
    }

    bool greater50()
    {
        return abs(xmin) > 50 || abs(xmax) > 50 || abs(ymin) > 50 || abs(ymax) > 50 || abs(zmin) > 50 || abs(zmax) > 50;
    }

    int64_t cube_num()
    {
        int64_t num = (xmax - xmin + 1) * (ymax - ymin + 1) * (zmax - zmin + 1);
        return turn ? num : -1 * num;
    }

    bool intersect(const cuboid &ot)
    {
        return (xmin <= ot.xmax && xmax >= ot.xmin) && (ymin <= ot.ymax && ymax >= ot.ymin) && (zmin <= ot.zmax && zmax >= ot.zmin);
    }

    cuboid intersect_cube(const cuboid &ot)
    {
        cuboid cu;
        cu.xmin = max(xmin, ot.xmin);
        cu.xmax = min(xmax, ot.xmax);

        cu.ymin = max(ymin, ot.ymin);
        cu.ymax = min(ymax, ot.ymax);

        cu.zmin = max(zmin, ot.zmin);
        cu.zmax = min(zmax, ot.zmax);

        cu.turn = !turn;

        return cu;
    }

    vector<tuple<int64_t, int64_t, int64_t>> getcube()
    {
        vector<tuple<int64_t, int64_t, int64_t>> r;
        for (int64_t x = xmin; x <= xmax; x++)
        {
            for (int64_t y = ymin; y <= ymax; y++)
            {
                for (int64_t z = zmin; z <= zmax; z++)
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

    set<tuple<int64_t, int64_t, int64_t>> cube_on;
    for (auto &cuboid : cuboids)
    {
        if (cuboid.turn && !cuboid.greater50())
        {
            for (auto &t : cuboid.getcube())
            {
                cube_on.insert(t);
            }
        }
        if (!cuboid.turn && !cuboid.greater50())
        {
            for (auto &t : cuboid.getcube())
            {
                cube_on.erase(t);
            }
        }
    }

    cout << cube_on.size() << endl;
}

void part2()
{
    ifstream ifs{"input\\input-22"};
    string line;

    vector<cuboid> cuboids;
    while (getline(ifs, line))
    {
        cuboids.push_back(line);
    }

    vector<cuboid> cu_piece;
    for (int i = 0; i < cuboids.size(); i++)
    {
        vector<cuboid> tmp;
        if (cuboids[i].turn)
        {
            tmp.emplace_back(cuboids[i]);
        }

        int len = cu_piece.size();
        for (int j = 0; j < len; j++)
        {
            if (cu_piece[j].intersect(cuboids[i]))
            {
                tmp.emplace_back(cu_piece[j].intersect_cube(cuboids[i]));
            }
        }

        for (auto &cu : tmp)
        {
            cu_piece.emplace_back(cu);
        }
    }

    int64_t sum = 0;
    for (auto &i : cu_piece)
    {
        sum += i.cube_num();
    }

    cout << sum << endl;
}

int main()
{
    part1();
    part2();
}