#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <string>
using namespace std;

void part1()
{
    bitset<12> gamma_rate;
    bitset<12> epsilon_rate;

    ifstream ifs{"input\\input-3"};
    int zero_count = 0;
    int one_count = 0;

    string line;
    vector<string> allLine;
    while (ifs >> line)
    {
        allLine.emplace_back(line);
    }
    //cout<<allLine.size()<<endl;
    for (int i = 0; i < 12; i++)
    {
        bitset<1000> v;
        for (int j = 0; j < allLine.size(); j++)
        {
            v[j] = allLine[j][i] - '0';
        }

        zero_count = 1000 - v.count();
        one_count = v.count();

        gamma_rate[i] = zero_count > one_count ? 0 : 1;
        epsilon_rate[i] = zero_count > one_count ? 1 : 0;
    }

    cout << stoi(gamma_rate.to_string(), 0, 2) * stoi(epsilon_rate.to_string(), 0, 2) << endl;
}

int main()
{
    part1();
}
