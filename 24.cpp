#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// instruction
struct instruction {
    int inx;    // inp,add,mul,div,mod,eql 0-5
    int reg;    // w,x,y,z 0-3;
    bool vn;    // variable or number;
    int op2;    // second oprand
};

function<int(int, int)> getfunc(int ins) {
    switch (ins) {
    case 1:
        return std::plus<int>();
    case 2:
        return std::multiplies<int>();
    case 3:
        return std::divides<int>();
    case 4:
        return modulus<int>();
    case 5:
        return equal_to<int>();
    default:
        return plus<int>();
    }
}

instruction parse_ins(const string& line) {
    instruction ins;
    ins.reg = line[4] - 'w';
    if (line.starts_with("inp")) {
        ins.inx = 0;
    } else {
        if (isdigit(line[6])) {
            ins.vn  = false;
            ins.op2 = stoi(line.substr(6, line.size() - 6));
        } else {
            ins.vn  = true;
            ins.op2 = line[6] - 'w';
        }

        if (line.starts_with("add")) {
            ins.inx = 1;

        } else if (line.starts_with("mul")) {
            ins.inx = 2;
        } else if (line.starts_with("div")) {
            ins.inx = 3;
        } else if (line.starts_with("mod")) {
            ins.inx = 4;
        } else
            ins.inx = 5;
    }
    return ins;
}


void part1() {
    ifstream input("input/input-24");
    vector<instruction> ins_vec;
    string line;
    while (getline(input, line)) {
        ins_vec.push_back(parse_ins(line));
    }

    // int64_t count;
    // auto start = chrono::system_clock::now();

    // test 1000000 time 0.6s, 
    for (int64_t i = 99'999'999'999'999; i >= 11'111'111'111'111; i--) {
        // count++;
        // if (count == 1'000'000) {
        //     auto end = chrono::system_clock::now();
        //     cout << end - start << endl;
        // }
        // cout << i << endl;
        vector<int> regs(4);
        string istr = to_string(i);
        if (!istr.contains('0')) {
            int inpinx = 0;
            for (auto& ins : ins_vec) {
                if (ins.inx == 0)    // inp
                {
                    regs[ins.reg] = istr[inpinx];
                    inpinx += 1;
                } else {
                    regs[ins.reg] = getfunc(ins.inx)(regs[ins.reg], ins.vn ? regs[ins.op2] : ins.op2);
                }
            }

            if (regs[3] == 0) {
                cout << i << endl;
            }
        }
    }
}

int main() {
    part1();
}