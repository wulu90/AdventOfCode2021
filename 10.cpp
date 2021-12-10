#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

void part1()
{
    ifstream ifs{"input\\input-10"};

    string line;
    char c;
    vector<char> nav_stack;
    vector<int> error_scores;

    map<char, int> points;
    points.insert({')', 3});
    points.insert({']', 57});
    points.insert({'}', 1197});
    points.insert({'>', 25137});

    map<char, char> nav_pairs;
    nav_pairs.insert({')', '('});
    nav_pairs.insert({']', '['});
    nav_pairs.insert({'}', '{'});
    nav_pairs.insert({'>', '<'});

    while (getline(ifs, line))
    {
        nav_stack.clear();
        istringstream iss{line};
        while (iss >> c)
        {
            if (c == '(' || c == '[' || c == '{' || c == '<')
            {
                nav_stack.push_back(c);
            }
            else
            {
                if (nav_stack.empty())
                {
                    error_scores.push_back(points[c]);
                    break;
                }
                else
                {
                    char last = nav_stack.back();
                    if (last == nav_pairs[c])
                    {
                        nav_stack.pop_back();
                    }
                    else
                    {
                        error_scores.push_back(points[c]);
                        break;
                    }
                }
            }
        }
    }

    int sum = 0;
    for (auto s : error_scores)
    {
        sum += s;
    }
    cout << sum << endl;
}

void part2()
{
    ifstream ifs{"input\\input-10"};

    string line;
    char c;
    vector<char> nav_stack;

    vector<int64_t> complete_scores;

    map<char, int> points;
    points.insert({')', 1});
    points.insert({']', 2});
    points.insert({'}', 3});
    points.insert({'>', 4});

    map<char, char> nav_pairs;
    nav_pairs.insert({')', '('});
    nav_pairs.insert({']', '['});
    nav_pairs.insert({'}', '{'});
    nav_pairs.insert({'>', '<'});

    map<char, char> nav_pairs_re;
    nav_pairs_re.insert({'(', ')'});
    nav_pairs_re.insert({'[', ']'});
    nav_pairs_re.insert({'{', '}'});
    nav_pairs_re.insert({'<', '>'});

    while (getline(ifs, line))
    {
        nav_stack.clear();
        istringstream iss{line};
        bool incomplete = true;
        while (iss >> c)
        {
            if (c == '(' || c == '[' || c == '{' || c == '<')
            {
                nav_stack.push_back(c);
            }
            else
            {
                if (nav_stack.empty())
                {
                    incomplete = false;
                    break;
                }
                else
                {
                    char last = nav_stack.back();
                    if (last == nav_pairs[c])
                    {
                        nav_stack.pop_back();
                    }
                    else
                    {
                        incomplete = false;
                        break;
                    }
                }
            }
        }

        if (incomplete)
        {
            int64_t score = 0;
            while (!nav_stack.empty())
            {
                auto c = nav_stack.back();
                score = score * 5 + points[nav_pairs_re[c]];
                nav_stack.pop_back();
            }
            complete_scores.push_back(score);
        }
    }

    sort(complete_scores.begin(), complete_scores.end());
    cout << *(complete_scores.begin() + complete_scores.size() / 2) << endl;
}

int main()
{
    part1();
    part2();
}
