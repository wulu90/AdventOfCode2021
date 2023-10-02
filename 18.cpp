#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

using namespace std;

vector<string> addition(const vector<string>& l, const vector<string>& r) {
    vector<string> res;
    res.push_back("[");
    copy(l.begin(), l.end(), back_inserter(res));
    res.push_back(",");
    copy(r.begin(), r.end(), back_inserter(res));
    res.push_back("]");
    return res;
}

void split(vector<string>& snailnum) {
    for (int i = 0; i < snailnum.size(); i++) {
        if (snailnum[i] != "[" && snailnum[i] != "]" && snailnum[i] != ",") {
            if (stoi(snailnum[i]) >= 10) {
                int temp = stoi(snailnum[i]);
                int l    = temp / 2;
                int r    = temp % 2 == 0 ? temp / 2 : (temp / 2) + 1;
                snailnum.erase(snailnum.begin() + i);
                snailnum.insert(snailnum.begin() + i, "]");
                snailnum.insert(snailnum.begin() + i, to_string(r));
                snailnum.insert(snailnum.begin() + i, ",");
                snailnum.insert(snailnum.begin() + i, to_string(l));
                snailnum.insert(snailnum.begin() + i, "[");
                break;
            }
        }
    }

    // for (auto& c : snailnum) {
    //     cout << c;
    // }
    // cout << endl;
}

void testSP() {
    // [[[[0,7],4],[[7,8],[0,13]]],[1,1]]
    vector<string> aa{"[", "[", "[", "[",  "0", ",", "7", "]", ",", "4", "]", ",", "[", "15", ",",
                      "[", "0", ",", "13", "]", "]", "]", ",", "[", "1", ",", "1", "]", "]"};

    split(aa);
    for (auto& a : aa) {
        cout << a;
    }
    cout << endl;
}

void explode(vector<string>& snailnum) {
    int depth = 0;
    for (int i = 0; i < snailnum.size(); i++) {
        if (snailnum[i] == "[") {
            depth += 1;
        } else if (snailnum[i] == "]") {
            depth -= 1;
        } else if (snailnum[i] == ",") {
            continue;
        } else {
            if (depth > 4) {
                int l = stoi(snailnum[i]);
                int r = stoi(snailnum[i + 2]);

                for (int j = i - 1; j >= 0; j--) {
                    if (snailnum[j] != "[" && snailnum[j] != "]" && snailnum[j] != ",") {
                        snailnum[j] = to_string(stoi(snailnum[j]) + l);
                        break;
                    }
                }

                for (int j = i + 3; j < snailnum.size(); j++) {
                    if (snailnum[j] != "[" && snailnum[j] != "]" && snailnum[j] != ",") {
                        snailnum[j] = to_string(stoi(snailnum[j]) + r);
                        break;
                    }
                }

                int k = i - 1;    // [
                snailnum.erase(snailnum.begin() + k, snailnum.begin() + k + 5);
                snailnum.insert(snailnum.begin() + k, "0");
                i = k;
                depth -= 1;

                // for (auto& c : snailnum) {
                //     cout << c;
                // }
                // cout << endl;
            }
        }
    }
}

void testX() {
    // string line = "[[[[[9,8],1],2],3],4]"; // [[[[0,9],2],3],4]
    // string line="[7,[6,[5,[4,[3,2]]]]]";  // [7,[6,[5,[7,0]]]]
    // string line = "[[6,[5,[4,[3,2]]]],1]"; // [[6,[5,[7,0]]],3]
    string line = "[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]";    // [[3,[2,[8,0]]],[9,[5,[7,0]]]]
    vector<string> aa;
    for (auto c : line) {
        aa.push_back({c});
    }
    explode(aa);
    for (auto a : aa) {
        cout << a;
    }
    cout << endl;
}

void magnitude(vector<string>& snailnum) {
    for (int i = 0; i < snailnum.size(); i++) {
        if (snailnum[i] == "]") {
            int mag = 3 * stoi(snailnum[i - 3]) + 2 * stoi(snailnum[i - 1]);
            int k   = i - 4;
            snailnum.erase(snailnum.begin() + k, snailnum.begin() + k + 5);
            snailnum.insert(snailnum.begin() + k, to_string(mag));

            for (int j = k; j >= 0; j--) {
                if (snailnum[j] == "[") {
                    i = j;
                    break;
                }
            }
        }
    }
}

void testMag() {
    // string line = "[[1,2],[[3,4],5]]";  // 143
    // string line = "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]"; // 1384
    // string line = "[[[[1,1],[2,2]],[3,3]],[4,4]]"; // 445
    // string line="[[[[3,0],[5,3]],[4,4]],[5,5]]";  // 791
    // string line="[[[[5,0],[7,4]],[5,5]],[6,6]]";  // 1137
    string line = "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]";    // 3488

    vector<string> aa;
    for (auto c : line) {
        aa.push_back({c});
    }

    magnitude(aa);

    cout << stoi(aa[0]) << endl;
}

// void test() {
//     testX();
//     testMag();
//     testSP();
// }

void part1() {
    // ifstream input("input/input-18test");
    ifstream input("input/input-18");

    string line;
    vector<string> inp;
    while (getline(input, line)) {
        inp.push_back(line);
    }

    vector<vector<string>> snailnums;
    for (auto& str : inp) {
        vector<string> s;
        for (auto& c : str) {
            s.push_back({c});    // all input number is 0...9 no biger than 9
        }
        snailnums.push_back(s);
    }

    vector<string> finalnum = snailnums[0];
    for (int i = 1; i < snailnums.size(); i++) {
        finalnum   = addition(finalnum, snailnums[i]);
        auto befor = finalnum;
        auto after = finalnum;
        // for (auto& c : finalnum) {
        //     cout << c;
        // }
        // cout << endl;
        do {
            befor = finalnum;
            explode(finalnum);
            split(finalnum);
            after = finalnum;
        } while (befor != after);

        // for (auto& c : finalnum) {
        //     cout << c;
        // }
        // cout << endl;
    }

    magnitude(finalnum);
    cout << finalnum[0] << endl;
}

int main() {
    part1();
}
