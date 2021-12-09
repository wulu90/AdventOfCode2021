#include <vector>
#include <iostream>
#include <ranges>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

void part1()
{
    ifstream ifs{"input\\input-7"};
    string line;
    getline(ifs, line);
    vector<int> numvec;

    auto split_v = views::split(line, ',');
    for (const auto &in : split_v)
    {
        string str(&*(in.begin()), ranges::distance(in));
        numvec.emplace_back(stoi(str));
    }

    sort(numvec.begin(), numvec.end());

    // https://en.wikipedia.org/wiki/Geometric_median
    // https://en.wikipedia.org/wiki/Geometric_median#cite_ref-haldane_11-0
    // For the 1-dimensional case, the geometric median coincides with the median. This is because the univariate median also minimizes the sum of distances from the points.
    int median = 0;
    int count = numvec.size();
    if (count % 2 == 0)
    {
        median = (numvec[count / 2 - 1] + numvec[count / 2]) / 2;
    }
    else
    {
        median = numvec[count / 2];
    }

    int fuel = 0;
    for (auto i : numvec)
    {
        fuel += abs(i - median);
    }
    cout << median << endl;
    cout << fuel << endl;
}

void part2()
{

    ifstream ifs{"input\\input-7"};
    string line;
    getline(ifs, line);
    vector<int> numvec;

    auto split_v = views::split(line, ',');
    for (const auto &in : split_v)
    {
        string str(&*(in.begin()), ranges::distance(in));
        numvec.emplace_back(stoi(str));
    }

    sort(numvec.begin(), numvec.end());

    int min = numeric_limits<int>::max();
    vector<int> costs;
    for (int i = numvec[0]; i < numvec[numvec.size() - 1]; i++)
    {
        int cost_sum = 0;
        for (auto n : numvec)
        {
            int dis = abs(n - i);
            cost_sum += (dis + 1) * dis / 2;
        }
        costs.emplace_back(cost_sum);
    }

    for (auto c : costs)
    {
        if (c < min)
        {
            min = c;
        }
    }

    cout << min << endl;
}

int main()
{
    part1();
    part2(); // brute force
}