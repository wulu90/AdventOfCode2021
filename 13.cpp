#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void foldx(int foldline, vector<vector<bool>> &paper);
void foldy(int foldline, vector<vector<bool>> &paper);
int count_dot(const vector<vector<bool>> &paper);
void print_paper(const vector<vector<bool>> &paper);
void part1(vector<pair<char, int>> &folds, vector<vector<bool>> paper);
void part2(vector<pair<char, int>> &folds, vector<vector<bool>> paper);

void foldx(int foldline, vector<vector<bool>> &paper)
{
    int row = paper.size();
    int col = paper[0].size();
    int foldwidth = col - foldline - 1;
    int left = foldline - foldwidth;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j <= foldwidth; j++)
        {
            paper[i][j + left] = paper[i][j + left] | paper[i][col - 1 - j];
        }
        paper[i].resize(foldline);
    }
}

void foldy(int foldline, vector<vector<bool>> &paper)
{
    int row = paper.size();
    int col = paper[0].size();
    int foldheight = row - foldline - 1;
    int top = foldline - foldheight;
    for (int i = 0; i < foldheight; i++)
    {
        for (int j = 0; j < col; j++)
        {
            paper[i + top][j] = paper[i + top][j] | paper[row - 1 - i][j];
        }
    }
    paper.resize(foldline);
}

int count_dot(const vector<vector<bool>> &paper)
{
    int row = paper.size();
    int col = paper[0].size();
    int count = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (paper[i][j])
            {
                count += 1;
            }
        }
    }
    return count;
}

void print_paper(const vector<vector<bool>> &paper)
{
    int row = paper.size();
    int col = paper[0].size();
    string line;
    line.resize(col);
    for (int i = 0; i < row; i++)
    {
        line.clear();
        for (int j = 0; j < col; j++)
        {
            if (paper[i][j])
            {
                line.push_back('#');
            }
            else
            {
                line.push_back('.');
            }
        }
        cout << line << endl;
    }
}

void part1(vector<pair<char, int>> &folds, vector<vector<bool>> paper)
{
    char dir = folds[0].first;
    int foldline = folds[0].second;
    if (dir == 'x')
    {
        foldx(foldline, paper);
    }
    else
    {
        foldy(foldline, paper);
    }

    cout << count_dot(paper) << endl;
}

void part2(vector<pair<char, int>> &folds, vector<vector<bool>> paper)
{
    for (auto [dir, foldline] : folds)
    {
        if (dir == 'x')
        {
            foldx(foldline, paper);
        }
        else
        {
            foldy(foldline, paper);
        }
    }

    cout << count_dot(paper) << endl;
    print_paper(paper);
}

int main()
{
    ifstream ifs{"input\\input-13"};
    string line;

    vector<pair<int, int>> dots;
    vector<pair<char, int>> folds;
    int xmax = 0;
    int ymax = 0;
    while (getline(ifs, line))
    {
        if (line.empty())
            continue;
        if (line.starts_with("fold"))
        {
            auto pos = line.find('=');
            auto c = line[pos - 1];
            auto foldline = stoi(line.substr(pos + 1, line.size()));
            folds.emplace_back(pair(c, foldline));
            continue;
        }
        auto pos = line.find(',');
        auto x = stoi(line.substr(0, pos));
        auto y = stoi(line.substr(pos + 1, line.size()));
        dots.emplace_back(pair(x, y));
        if (x > xmax)
        {
            xmax = x;
        }
        if (y > ymax)
        {
            ymax = y;
        }
    }

    vector<vector<bool>> paper;
    paper.resize(ymax + 1);
    for (auto &v : paper)
    {
        v.resize(xmax + 1);
    }
    for (auto [x, y] : dots)
    {
        paper[y][x] = true;
    }

    part1(folds, paper);
    part2(folds, paper);
}
