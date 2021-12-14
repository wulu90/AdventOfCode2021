#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
void part1()
{
    ifstream ifs{"input\\input-14"};
    string line;

    vector<char> polymer;
    getline(ifs, line);
    for (auto &c : line)
    {
        polymer.emplace_back(c);
    }
    getline(ifs, line); // skip blank

    map<string, char> insertion_rules;
    while (getline(ifs, line))
    {
        auto pos = line.find("->");
        auto s1 = line.substr(0, pos - 1);
        auto s2 = line.substr(pos + 3, line.size());
        insertion_rules[s1] = s2[0];
    }

    vector<char> tmp;
    for (size_t i = 0; i < 10; i++)
    {
        auto len = polymer.size();
        tmp.clear();
        tmp.push_back(polymer[0]);
        string str;
        for (size_t j = 0; j < len - 1; j++)
        {
            str.clear();
            str.push_back(polymer[j]);
            str.push_back(polymer[j + 1]);

            //tmp.push_back(polymer[j]);
            tmp.push_back(insertion_rules[str]);
            tmp.push_back(polymer[j + 1]);
        }
        polymer.swap(tmp);
        cout << i << endl;
    }

    map<char, size_t> char_count;
    for (auto &c : polymer)
    {
        char_count[c] += 1;
    }
    vector<size_t> counts;
    for (auto &[c, i] : char_count)
    {
        counts.push_back(i);
    }
    sort(counts.begin(), counts.end());
    cout << counts[counts.size() - 1] - counts[0] << endl;
}

int main()
{
    part1();
}
