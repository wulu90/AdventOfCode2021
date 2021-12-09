#include <iostream>
#include <fstream>
#include <string>
#include <deque>

using namespace std;

void part1()
{
    ifstream ifs{"input\\input-1"};

    if (!ifs.is_open())
    {
        cout << "fail to open input" << endl;
    }
    else
    {
        int prev;
        int cur;
        int count = 0;
        ifs >> prev;

        while (ifs >> cur)
        {
            if (cur > prev)
            {
                count++;
            }
            prev = cur;
        }
        cout << count << endl;
    }
}

bool compare(const deque<int> &d1, const deque<int> &d2)
{
    int sum1 = 0;
    int sum2 = 0;
    int size = d1.size();
    for (int i = 0; i < size; i++)
    {
        sum1 += d1[i];
        sum2 += d2[i];
    }
    if (sum2 > sum1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void part2()
{
    ifstream ifs{"input\\input-1"};

    if (!ifs.is_open())
    {
        cout << "fail to open input" << endl;
    }
    else
    {
        int n;
        int count = 0;
        deque<int> first;
        deque<int> second;
        ifs >> n;
        first.push_back(n);
        ifs >> n;
        first.push_back(n);
        second.push_back(n);
        ifs >> n;
        first.push_back(n);
        second.push_back(n);

        while (ifs >> n)
        {
            second.push_back(n);
            if (compare(first, second))
            {
                count++;
            }
            first.pop_front();
            first.push_back(n);
            second.pop_front();
        }
        cout << count << endl;
    }
}

int main(int argc, char **argv)
{
    part1();
    part2();
}
