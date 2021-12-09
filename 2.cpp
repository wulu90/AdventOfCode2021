#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void part1()
{
    ifstream ifs{"input-2"};
    size_t horizon = 0;
    size_t depth = 0;
    string command;
    size_t units;
    while (ifs >> command)
    {
        ifs >> units;
        if (command == "forward")
        {
            horizon += units;
        }
        else if (command == "down")
        {
            depth += units;
        }
        else if (command == "up")
        {
            depth -= units;
        }
    }


    cout << (horizon * depth) << endl;
}

void part2()
{
    ifstream ifs{"input-2"};
    size_t horizon = 0;
    size_t depth = 0;
    size_t aim = 0;
    string command;
    size_t units;
    while (ifs >> command)
    {
        ifs >> units;
        if (command == "forward")
        {
            horizon += units;
            depth += aim * units;
        }
        else if (command == "down")
        {
            aim += units;
        }
        else if (command == "up")
        {
            aim -= units;
        }
    }

    cout << horizon * depth << endl;
}

int main()
{
    part1();
    part2();
}
