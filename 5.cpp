#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdio>

using namespace std;

class point
{
public:
    point() {}
    point(int _x, int _y) : x(_x), y(_y) {}
    int x;
    int y;
};

class line
{
public:
    line() {}
    line(int x1, int y1, int x2, int y2) : start(x1, y1), end(x2, y2) {}

    bool is_vertical()
    {
        return start.x == end.x;
    }

    bool is_horizontal()
    {
        return start.y == end.y;
    }

    bool is_45diagnol()
    {
        return abs(start.x - end.x) == abs(start.y - end.y);
    }

    vector<point> cover_points()
    {
        vector<point> cps;
        if (is_vertical())
        {
            int y1 = min(start.y, end.y);
            int y2 = max(start.y, end.y);
            for (int i = y1; i <= y2; i++)
            {
                point p;
                p.x = start.x;
                p.y = i;
                cps.emplace_back(p);
            }
        }
        if (is_horizontal())
        {
            int x1 = min(start.x, end.x);
            int x2 = max(start.x, end.x);
            for (int i = x1; i <= x2; i++)
            {
                point p;
                p.x = i;
                p.y = start.y;
                cps.emplace_back(p);
            }
        }
        // for part2
        if (is_45diagnol())
        {
            int dis = abs(start.x - end.x);
            int x_step = start.x < end.x ? 1 : -1;
            int y_step = start.y < end.y ? 1 : -1;
            for (int i = 0; i <= dis; i++)
            {
                point p;
                p.x = start.x + i * x_step;
                p.y = start.y + i * y_step;
                cps.emplace_back(p);
            }
        }
        return cps;
    }

private:
    point start;
    point end;
};

void part1()
{

    ifstream ifs{"input\\input-5"};
    string line_str;

    vector<line> lines;

    while (getline(ifs, line_str))
    {
        int x1, y1, x2, y2;
        sscanf(line_str.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
        line l{x1, y1, x2, y2};
        lines.emplace_back(l);
    }

    //cout << lines.size() << endl;

    vector<point> hv_points;
    int xmax = 0;
    int ymax = 0;
    for (auto &l : lines)
    {
        for (auto &p : l.cover_points())
        {
            xmax = max(xmax, p.x);
            ymax = max(ymax, p.y);
            hv_points.emplace_back(p);
        }
    }

    //int* allp=new int[xmax*ymax];
    vector<int> allp((xmax + 1) * (ymax + 1));
    for (auto &p : hv_points)
    {
        allp[p.y * xmax + p.x] += 1;
    }
    int count = 0;
    for (auto c : allp)
    {
        if (c > 1)
        {
            count += 1;
        }
    }
    cout << count << endl;
}

int main()
{
    part1();
}