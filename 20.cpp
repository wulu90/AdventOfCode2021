#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void emhance(vector<vector<char>> &image, const string &algo, char &inf)
{
    for (auto &row : image)
    {
        row.insert(row.begin(), inf);
        row.insert(row.end(), inf);
    }
    auto col_count = image[0].size();
    vector<char> top(col_count, inf);
    image.insert(image.begin(), top);
    image.insert(image.end(), top);

    vector<pair<size_t, size_t>> dirs{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    vector<vector<char>> tmp;
    tmp.resize(image.size());
    for (auto &row : tmp)
    {
        row.resize(image[0].size());
    }

    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            string inx;
            for (auto &[r, c] : dirs)
            {
                if (i + r < 0 || i + r > image.size() - 1 || j + c < 0 || j + c > image[0].size() - 1)
                {
                    if (inf == '.')
                    {
                        inx.push_back('0');
                    }
                    else if (inf == '#')
                    {
                        inx.push_back('1');
                    }
                }
                else
                {
                    if (image[i + r][j + c] == '#')
                    {
                        inx.push_back('1');
                    }
                    else if (image[i + r][j + c] == '.')
                    {
                        inx.push_back('0');
                    }
                }
            }
            tmp[i][j] = algo[stoi(inx, 0, 2)];
        }
    }

    image.swap(tmp);

    int change_inx = inf == '.' ? 0b000000000 : 0b111111111;
    inf = algo[change_inx];
}

void part1()
{
    ifstream ifs{"input\\input-20"};
    string line;

    string algo;
    getline(ifs, algo);

    getline(ifs, line); // skip blank;

    vector<vector<char>> image;
    while (getline(ifs, line))
    {
        vector<char> cl;
        cl.reserve(line.size());
        for (auto &c : line)
        {
            cl.emplace_back(c);
        }
        image.emplace_back(cl);
    }

    char inf = '.';
    emhance(image, algo, inf);
    emhance(image, algo, inf);

    int count = 0;
    for (auto &row : image)
    {
        for (auto &c : row)
        {
            if (c == '#')
            {
                count += 1;
            }
        }
    }

    cout << count << endl;
}

void part2()
{
    ifstream ifs{"input\\input-20"};
    string line;

    string algo;
    getline(ifs, algo);

    getline(ifs, line); // skip blank;

    vector<vector<char>> image;
    while (getline(ifs, line))
    {
        vector<char> cl;
        cl.reserve(line.size());
        for (auto &c : line)
        {
            cl.emplace_back(c);
        }
        image.emplace_back(cl);
    }

    char inf = '.';
    for (int i = 0; i < 50; i++)
    {
        emhance(image, algo, inf);
    }

    int count = 0;
    for (auto &row : image)
    {
        for (auto &c : row)
        {
            if (c == '#')
            {
                count += 1;
            }
        }
    }

    cout << count << endl;
}

int main()
{
    part1();
    part2();
}