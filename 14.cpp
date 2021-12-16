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
        auto s2 = line.substr(pos + 3, line.size() - pos - 3);
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

            tmp.push_back(insertion_rules[str]);
            tmp.push_back(polymer[j + 1]);
        }
        polymer.swap(tmp);
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

void part2()
{
    ifstream ifs{"input\\input-14"};
    string line;

    string polymer;
    getline(ifs, polymer);

    getline(ifs, line); // skip blank

    // like {"HB":["HC","CB"]},{"KO":["KS","SO"]}....
    map<string, vector<string>> insertion_rules;
    while (getline(ifs, line))
    {
        auto pos = line.find("->");
        auto s1 = line.substr(0, pos - 1);
        auto s2 = line.substr(pos + 3, line.size() - pos - 3);

        insertion_rules[s1].push_back({s1[0], s2[0]});
        insertion_rules[s1].push_back({s2[0], s1[1]});
    }

    // {"NN":1},{"NC":1},{"CB":1}
    map<string, int64_t> pattern_count;
    for (int i = 0; i < polymer.size() - 1; i++)
    {
        pattern_count[{polymer[i], polymer[i + 1]}] += 1;
    }

    // NNCB -> NN NC CB
    // NCNBCHB -> NC CN  NB BC  CH HB
    // NBCCNBBBCBHCB -> NB BC  CC CN  NB BB  BB CB  CB BH  HC CB
    // because the mid char is the second char of the before string and the first of after string
    // so just sum the count of all the 2nd char of all string
    // and add the 1st char of the template

    map<string, int64_t> tmp_count;
    for (int i = 0; i < 40; i++)
    {
        tmp_count.clear();
        for (auto &[str, num] : pattern_count)
        {
            tmp_count[insertion_rules[str][0]] += num;
            tmp_count[insertion_rules[str][1]] += num;
        }
        pattern_count.swap(tmp_count);
    }

    map<char, int64_t> char_count;
    for (auto &[str, num] : pattern_count)
    {
        char_count[str[1]] += num;
    }
    char_count[polymer[0]] += 1;

    vector<int64_t> counts;
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
    part2();
}
