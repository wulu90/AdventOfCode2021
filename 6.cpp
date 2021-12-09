#include <vector>
#include <iostream>
#include <ranges>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{

    ifstream ifs{"input\\input-6"};
    string line;
    getline(ifs, line);
    vector<int> numvec;

    auto split_v = views::split(line, ',');
    for (const auto &in : split_v)
    {
        string str(&*(in.begin()), ranges::distance(in));
        numvec.emplace_back(stoi(str));
    }

    vector<int64_t> status(9);
    for (auto i : numvec)
    {
        status[i] += 1;
    }

    for (int i = 0; i < 80; i++)
    {
        rotate(status.begin(), status.begin() + 1, status.end());
        status[6] += status[8];
    }

    int64_t sum = 0;
    for (auto i : status)
    {
        sum += i;
    }

    cout << sum << endl;

    for (int i = 80; i < 256; i++)
    {
        rotate(status.begin(), status.begin() + 1, status.end());
        status[6] += status[8];
    }

    sum = 0;
    for (auto i : status)
    {
        sum += i;
    }

    cout << sum << endl;
}