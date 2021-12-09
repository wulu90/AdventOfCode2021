#include <fstream>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <bitset>
#include <ranges>
#include <vector>
#include <map>

using namespace std;

void part1()
{

    ifstream ifs{"input\\input-8"};

    vector<vector<string>> all_str;

    string row_line;
    while (getline(ifs, row_line))
    {
        auto sv = views::split(row_line, " | ");
        vector<string> row_strs;
        for (const auto long_str : sv)
        {
            for (const auto s : views::split(long_str, ' '))
            {
                string str(&*s.begin(), ranges::distance(s));
                if (!(str == "|"))
                {
                    row_strs.emplace_back(str);
                }
            }
        }
        all_str.emplace_back(row_strs);
    }

    int count = 0;
    for (const auto &strv : all_str)
    {
        int v_size = strv.size();
        for (int i = 0; i < 4; i++)
        {
            int str_size = strv[v_size - 1 - i].size();
            if (str_size == 2 || str_size == 4 || str_size == 3 || str_size == 7) // 1,4,7,8
            {
                count += 1;
            }
        }
    }

    cout << count << endl;
}

void write_bitset(bitset<7> &bs, const string &str)
{
    for (const char &c : str)
    {
        bs[c - 'a'] = true;
    }
}

int find_only_true_index(bitset<7> &bs)
{
    int inx = 0;
    for (int i = 0; i < 7; i++)
    {
        if (bs[i] == true)
        {
            inx = i;
            break;
        }
    }
    return inx;
}

void part2()
{
    ifstream ifs{"input\\input-8"};

    vector<vector<string>> all_str;

    string row_line;
    while (getline(ifs, row_line))
    {
        auto sv = views::split(row_line, " | ");
        vector<string> row_strs;
        for (const auto long_str : sv)
        {
            for (const auto s : views::split(long_str, ' '))
            {
                string str(&*s.begin(), ranges::distance(s));
                if (!(str == "|"))
                {
                    row_strs.emplace_back(str);
                }
            }
        }
        all_str.emplace_back(row_strs);
    }

    vector<int> four_v;
    for (auto &line_str_vec : all_str)
    {
        set<string> str_set;
        for (auto s : line_str_vec)
        {
            sort(s.begin(), s.end());
            str_set.insert(s);
        }

        bitset<7> bs_1{false};      // 1
        bitset<7> bs_7{false};      // 7
        bitset<7> bs_4{false};      // 4
        bitset<7> bs_8{false};      // 8
        vector<bitset<7>> bs_2_3_5; // 2,3,5
        vector<bitset<7>> bs_0_6_9; // 0,6,9

        for (auto &s : str_set)
        {
            bitset<7> tmp{false};
            switch (s.size())
            {
            case 2:
                write_bitset(bs_1, s);
                break;
            case 3:
                write_bitset(bs_7, s);
                break;
            case 4:
                write_bitset(bs_4, s);
                break;
            case 7:
                write_bitset(bs_8, s);
                break;
            case 5:
                write_bitset(tmp, s);
                bs_2_3_5.push_back(tmp);
                break;
            case 6:
                write_bitset(tmp, s);
                bs_0_6_9.push_back(tmp);
                break;
            }
        }

        int a, b, c, d, e, f, g;
        a = b = c = d = e = f = g = 0;
        bitset<7> bs_6{false};
        for (auto &s6 : bs_0_6_9)
        {
            auto less_f = (s6 ^ bs_8) ^ bs_1;
            if (less_f.count() == 1) // find 6
            {
                f = find_only_true_index(less_f);

                auto c_bs = less_f ^ bs_1;
                c = find_only_true_index(c_bs);

                bitset<7> cf_bs{false};
                cf_bs[c] = true;
                cf_bs[f] = true;
                auto a_bs = cf_bs ^ bs_7;
                a = find_only_true_index(a_bs);

                bs_6 = s6;
                break;
            }
        }

        bitset<7> bs_0{false};
        for (auto &s3 : bs_2_3_5)
        {
            auto less_becf = (s3 ^ bs_8) ^ bs_1;
            if (less_becf.count() == 4) // find 3
            {
                auto dg_bs = s3 ^ bs_7;
                for (auto &s0 : bs_0_6_9)
                {
                    if (s0 != bs_6 && (bs_8 ^ s0 ^ dg_bs).count() == 1)
                    {
                        auto g_bs = bs_8 ^ s0 ^ dg_bs;
                        g = find_only_true_index(g_bs);
                        auto d_bs = g_bs ^ dg_bs;
                        d = find_only_true_index(d_bs);
                        bs_0 = s0;
                        break;
                    }
                }
            }
        }

        for (auto &s9 : bs_0_6_9)
        {
            if (s9 != bs_6 && s9 != bs_0) // find 9
            {
                auto e_bs = s9 ^ bs_8;
                e = find_only_true_index(e_bs);
            }
        }

        for (int i = 0; i < 7; i++)
        {
            if (i != a && i != c && i != d && i != e && i != f && i != g)
            {
                b = i;
                break;
            }
        }

        map<int, char> i_c;
        char ch[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
        i_c.insert({'a' - 'a', ch[a]});
        i_c.insert({'b' - 'a', ch[b]});
        i_c.insert({'c' - 'a', ch[c]});
        i_c.insert({'d' - 'a', ch[d]});
        i_c.insert({'e' - 'a', ch[e]});
        i_c.insert({'f' - 'a', ch[f]});
        i_c.insert({'g' - 'a', ch[g]});

        map<string, int> str_i;

        string str_0{i_c[0], i_c[1], i_c[2], i_c[4], i_c[5], i_c[6]};
        sort(str_0.begin(), str_0.end());
        str_i.insert({str_0, 0});

        string str_1{i_c[2], i_c[5]};
        sort(str_1.begin(), str_1.end());
        str_i.insert({str_1, 1});

        string str_2{i_c[0], i_c[2], i_c[3], i_c[4], i_c[6]};
        sort(str_2.begin(), str_2.end());
        str_i.insert({str_2, 2});

        string str_3{i_c[0], i_c[2], i_c[3], i_c[5], i_c[6]};
        sort(str_3.begin(), str_3.end());
        str_i.insert({str_3, 3});

        string str_4{i_c[1], i_c[2], i_c[3], i_c[5]};
        sort(str_4.begin(), str_4.end());
        str_i.insert({str_4, 4});

        string str_5{i_c[0], i_c[1], i_c[3], i_c[5], i_c[6]};
        sort(str_5.begin(), str_5.end());
        str_i.insert({str_5, 5});

        string str_6{i_c[0], i_c[1], i_c[3], i_c[4], i_c[5], i_c[6]};
        sort(str_6.begin(), str_6.end());
        str_i.insert({str_6, 6});

        string str_7{i_c[0], i_c[2], i_c[5]};
        sort(str_7.begin(), str_7.end());
        str_i.insert({str_7, 7});

        string str_8{i_c[0], i_c[1], i_c[2], i_c[3], i_c[4], i_c[5], i_c[6]};
        sort(str_8.begin(), str_8.end());
        str_i.insert({str_8, 8});

        string str_9{i_c[0], i_c[1], i_c[2], i_c[3], i_c[5], i_c[6]};
        sort(str_9.begin(), str_9.end());
        str_i.insert({str_9, 9});

        vector<int> output_values;
        for (int i = 3; i >= 0; i--)
        {
            auto s = *(line_str_vec.rbegin() + i);
            sort(s.begin(), s.end());
            output_values.push_back(str_i[s]);
        }

        auto ov = output_values[0] * 1000 + output_values[1] * 100 + output_values[2] * 10 + output_values[3];
        four_v.push_back(ov);
    }

    int sum = 0;
    for (auto i : four_v)
    {
        sum += i;
    }
    cout << sum << endl;
}
int main()
{
    part1();
    part2();
}
