#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <deque>

using namespace std;

bool is_all_lowercase(const string &str)
{
    for (auto &c : str)
    {
        if (isupper(c))
        {
            return false;
        }
    }
    return true;
}

void part1_non_recursive(map<string, vector<string>> &map_table)
{
    deque<string> path;
    deque<vector<string>> to_que;
    set<string> has_visited;
    int p_count = 0;
    path.push_back("start");
    to_que.push_back(map_table["start"]);

    while (!path.empty())
    {
        has_visited.clear();
        for (auto s : path)
        {
            has_visited.insert(s);
        }
        auto &to_vec = to_que.back();
        if (!to_vec.empty())
        {
            auto to_str = to_vec[0];
            if (is_all_lowercase(to_str))
            {
                if (has_visited.contains(to_str))
                {
                    to_vec.erase(to_vec.begin());
                    continue;
                }
                else
                {
                    path.push_back(to_str);
                    to_vec.erase(to_vec.begin());
                    to_que.push_back(map_table[to_str]);
                }
            }
            else
            {
                path.push_back(to_str);
                to_vec.erase(to_vec.begin());
                to_que.push_back(map_table[to_str]);
            }
        }
        else
        {
            path.pop_back();
            to_que.pop_back();
            continue;
        }

        if (path.back() == "end")
        {
            p_count += 1;
            path.pop_back();
            to_que.pop_back();
        }
    }

    cout << "non_recursive_part1:" << p_count << endl;
}

void part2_non_recursive(map<string, vector<string>> &map_table)
{
    deque<string> path;
    deque<vector<string>> to_que;
    map<string, int> has_visited;
    int p_count = 0;
    path.push_back("start");
    to_que.push_back(map_table["start"]);

    while (!path.empty())
    {
        has_visited.clear();
        for (auto s : path)
        {
            if (is_all_lowercase(s))
            {
                has_visited[s] += 1;
            }
        }
        auto &to_vec = to_que.back();
        if (!to_vec.empty())
        {
            auto to_str = to_vec[0];
            if (is_all_lowercase(to_str))
            {
                if (has_visited.contains(to_str))
                {
                    if (to_str == "start")
                    {
                        to_vec.erase(to_vec.begin());
                        continue;
                    }
                    bool two_visit = false;
                    for (auto [c, i] : has_visited)
                    {
                        if (i >= 2)
                            two_visit = true;
                    }
                    if (two_visit)
                    {
                        to_vec.erase(to_vec.begin());
                        continue;
                    }
                    else
                    {
                        path.push_back(to_str);
                        to_vec.erase(to_vec.begin());
                        to_que.push_back(map_table[to_str]);
                    }
                }
                else
                {
                    path.push_back(to_str);
                    to_vec.erase(to_vec.begin());
                    to_que.push_back(map_table[to_str]);
                }
            }
            else
            {
                path.push_back(to_str);
                to_vec.erase(to_vec.begin());
                to_que.push_back(map_table[to_str]);
            }
        }
        else
        {
            path.pop_back();
            to_que.pop_back();
            continue;
        }

        if (path.back() == "end")
        {
            p_count += 1;
            path.pop_back();
            to_que.pop_back();
        }
    }

    cout << "non_recursive_part2:" << p_count << endl;
}

void path_finder(string from, deque<string> path, map<string, vector<string>> &map_table, set<string> smalls, int &allcount)
{
    if (from == "end")
    {
        allcount += 1;
        return;
    }

    if (is_all_lowercase(from))
    {
        if (smalls.contains(from))
        {
            return;
        }
        else
        {
            path.emplace_back(from);
            smalls.insert(from);
            if (map_table[from].size() > 0)
            {
                for (auto s : map_table[from])
                {
                    path_finder(s, path, map_table, smalls, allcount);
                }
            }
        }
    }
    else
    {
        path.emplace_back(from);
        if (map_table[from].size() > 0)
        {
            for (auto s : map_table[from])
            {
                path_finder(s, path, map_table, smalls, allcount);
            }
        }
    }
}

void path_finder2(string from, deque<string> path, map<string, vector<string>> &map_table, map<string, int8_t> smalls_time, int &allcount)
{
    if (from == "end")
    {
        allcount += 1;
        return;
    }

    if (is_all_lowercase(from))
    {
        if (smalls_time.contains(from))
        {
            if (from == "start")
                return;
            bool has_two_visit = false;
            for (auto [s, i] : smalls_time)
            {
                if (i >= 2)
                {
                    has_two_visit = true;
                }
            }
            if (has_two_visit)
                return;

            path.emplace_back(from);
            smalls_time[from] += 1;
            for (auto c : map_table[from])
            {
                path_finder2(c, path, map_table, smalls_time, allcount);
            }
        }
        else
        {
            path.emplace_back(from);
            smalls_time[from] = 1;
            if (map_table[from].size() > 0)
            {
                for (auto s : map_table[from])
                {
                    path_finder2(s, path, map_table, smalls_time, allcount);
                }
            }
        }
    }
    else
    {
        path.emplace_back(from);
        if (map_table[from].size() > 0)
        {
            for (auto s : map_table[from])
            {
                path_finder2(s, path, map_table, smalls_time, allcount);
            }
        }
    }
}

int main()
{
    ifstream ifs{"input\\input-12"};
    string line;

    map<string, vector<string>> adj_table;
    while (getline(ifs, line))
    {
        auto pos = line.find('-');
        auto s1 = line.substr(0, pos);
        auto s2 = line.substr(pos + 1, line.size() - pos - 1);
        adj_table[s1].push_back(s2);
        adj_table[s2].push_back(s1);
    }

    deque<string> path_deque;

    path_deque.emplace_back("start");

    int allcount = 0;
    set<string> smalls;
    deque<string> path;
    path_finder("start", path, adj_table, smalls, allcount);
    cout << allcount << endl;

    part1_non_recursive(adj_table);
    part2_non_recursive(adj_table);
    // recursive is work, but too slow
    int allcount2 = 0;
    map<string, int8_t> smalls_time;
    deque<string> path2;
    path_finder2("start", path2, adj_table, smalls_time, allcount2);
    cout << allcount2 << endl;
}
