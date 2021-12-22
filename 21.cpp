#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
//#include <array>

using namespace std;

void part1()
{
    ifstream ifs{"input\\input-21"};
    string line;
    vector<int> players;
    while (getline(ifs, line))
    {
        auto pos = line.find(':');
        players.push_back(stoi(line.substr(pos + 2, line.size() - pos - 2)));
    }

    vector<int> score{0, 0};

    int roll = 0;

    while (true)
    {
        int player_index = roll % 2;

        int roll_sum = (roll > 100 ? roll - 100 : roll) * 3 * 3 + 6; // roll*3+1+roll*3+2+roll*3+3
        players[player_index] = (players[player_index] + roll_sum % 10) > 10 ? (players[player_index] + roll_sum % 10) % 10 : players[player_index] + roll_sum % 10;
        score[player_index] += players[player_index];

        roll += 1;
        if (score[0] >= 1000 || score[1] >= 1000)
        {
            break;
        }
    }
    cout << roll * 3 * min(score[0], score[1]) << endl;
}

pair<int64_t, int64_t> roll_move(bool player1, int64_t pos1, int64_t score1, int64_t pos2, int64_t score2, map<int64_t, int64_t> &rolls_sum)
{
    if (score1 >= 21)
    {
        return {1, 0};
    }

    if (score2 >= 21)
    {
        return {0, 1};
    }

    if (player1)
    {
        pair<int64_t, int64_t> sum;
        for (auto &[r, s] : rolls_sum)
        {
            auto newpos = pos1 + r > 10 ? pos1 + r - 10 : pos1 + r;
            auto [s1, s2] = roll_move(false, newpos, score1 + newpos, pos2, score2, rolls_sum);
            sum.first += s1 * s;
            sum.second += s2 * s;
        }
        return sum;
    }
    else
    {
        pair<int64_t, int64_t> sum;
        for (auto &[r, s] : rolls_sum)
        {
            auto newpos = pos2 + r > 10 ? pos2 + r - 10 : pos2 + r;
            auto [s1, s2] = roll_move(true, pos1, score1, newpos, score2 + newpos, rolls_sum);
            sum.first += s1 * s;
            sum.second += s2 * s;
        }
        return sum;
    }
}

void part2()
{
    ifstream ifs{"input\\input-21"};
    string line;
    vector<int64_t> players;
    while (getline(ifs, line))
    {
        auto pos = line.find(':');
        players.push_back(stoi(line.substr(pos + 2, line.size() - pos - 2)));
    }

    vector<int64_t> sv{0};
    for (int i = 0; i < 3; i++)
    {
        vector<int64_t> tmp;
        for (auto r : sv)
        {
            tmp.push_back(r + 1);
            tmp.push_back(r + 2);
            tmp.push_back(r + 3);
        }
        sv.swap(tmp);
    }

    map<int64_t, int64_t> rolls_sum;
    for (auto r : sv)
    {
        rolls_sum[r] += 1;
    }

    auto [a, b] = roll_move(true, players[0], 0, players[1], 0, rolls_sum);
    cout << a << endl
         << b << endl;
    cout << max(a, b) << endl;
}

int main()
{
    part1();
    part2();
}