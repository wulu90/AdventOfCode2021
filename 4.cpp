#include <map>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <sstream>

using namespace std;

class broad
{
public:
    broad() : marked{false}, has_wined{false} {}

    broad(const map<int, int> &n_i_p) : marked{false}, has_wined{false}
    {
        //num_index = n_i;
        for (const auto &n_i : n_i_p)
        {
            num_index.insert({n_i.first, n_i.second});
        }
    }

    bool marked_then_winned(int n)
    {
        if (has_wined)
            return has_wined;

        if (num_index.contains(n))
        {
            int inx = num_index[n];
            marked[inx] = true;

            bool r0 = marked[0] && marked[1] && marked[2] && marked[3] && marked[4];
            bool r1 = marked[5] && marked[6] && marked[7] && marked[8] && marked[9];
            bool r2 = marked[10] && marked[11] && marked[12] && marked[13] && marked[14];
            bool r3 = marked[15] && marked[16] && marked[17] && marked[18] && marked[19];
            bool r4 = marked[20] && marked[21] && marked[22] && marked[23] && marked[24];

            bool c0 = marked[0] && marked[5] && marked[10] && marked[15] && marked[20];
            bool c1 = marked[1] && marked[6] && marked[11] && marked[16] && marked[21];
            bool c2 = marked[2] && marked[7] && marked[12] && marked[17] && marked[22];
            bool c3 = marked[3] && marked[8] && marked[13] && marked[18] && marked[23];
            bool c4 = marked[4] && marked[9] && marked[14] && marked[19] && marked[24];

            has_wined = r0 || r1 || r2 || r3 || r4 || c0 || c1 || c2 || c3 || c4;
            return has_wined;
        }
        else
        {
            return has_wined;
        }
    }

    int calc_unmarked()
    {
        int sum = 0;
        for (auto &n_i : num_index)
        {
            if (!marked[n_i.second])
            {
                sum += n_i.first;
            }
        }
        return sum;
    }

    bool haswind() { return has_wined; }

private:
    map<int, int> num_index;
    //int marked[25];
    bitset<25> marked;
    bool has_wined;
};

void part1()
{
    ifstream ifs{"input\\input-4"};

    string line;
    getline(ifs, line);
    vector<int> numvec;

    auto split_v = views::split(line, ',');
    for (const auto &in : split_v)
    {
        string str(&*(in.begin()), ranges::distance(in));
        numvec.emplace_back(atoi(str.c_str()));
    }

    int broad_n;
    vector<int> all_n;
    while (ifs >> broad_n)
    {
        all_n.emplace_back(broad_n);
    }
    ifs.close();

    vector<broad> broads;
    for (int i = 0; i < all_n.size() / 25; i++)
    {
        map<int, int> n_i;
        for (int j = 0; j < 25; j++)
        {
            n_i.insert({all_n[i * 25 + j], j});
        }
        broad b{n_i};
        broads.emplace_back(b);
    }

    //bool haswin = false;
    //int unmarked_sum = 0;
    for (auto &in : numvec)
    {
        for (auto &b : broads)
        {
            if (!b.haswind())
            {
                if (b.marked_then_winned(in))
                {
                    //haswin = true;
                    //unmarked_sum = b.calc_unmarked();
                    //cout << unmarked_sum << endl;
                    cout << b.calc_unmarked() << endl;
                    cout << b.calc_unmarked() * in << endl;
                    //break;
                }
            }
        }
        // if (haswin)
        // {
        //     cout << in * unmarked_sum << endl;
        //     break;
        // }
    }
}

int main()
{
    part1();
}