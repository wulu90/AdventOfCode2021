#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void part()
{
    FILE *f = fopen("input\\input-17", "r");
    int x1, x2, y1, y2;
    fscanf(f, "target area: x=%d..%d, y=%d..%d", &x1, &x2, &y1, &y2);
    fclose(f);

    vector<int> ymax_vec;
    int init_v = 0;

    for (int xv0 = 1; xv0 <= x2; xv0++)
    {
        for (int yv0 = y1; yv0 < 1000; yv0++)
        {
            int xv = xv0;
            int yv = yv0;
            int px = 0;
            int py = 0;
            int ymax = 0;
            while (true)
            {
                px = px + xv;
                py = py + yv;
                xv = xv == 0 ? 0 : xv - 1;
                yv = yv - 1;
                if (py > ymax)
                {
                    ymax = py;
                }
                if (px <= x2 && px >= x1 && py >= y1 && py <= y2) // within the area
                {
                    ymax_vec.push_back(ymax);
                    init_v += 1;
                    break;
                }

                if (px > x2 || py < y1)
                { // never back
                    break;
                }
            }
        }
    }
    sort(ymax_vec.begin(), ymax_vec.end());
    cout << ymax_vec.back() << endl;
    cout << init_v << endl;
}

int main()
{
    part();
}