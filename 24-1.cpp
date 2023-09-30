#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<int> divs{1, 1, 1, 1, 26, 1, 26, 1, 1, 26, 26, 26, 26, 26};
vector<int> addx{15, 15, 12, 13, -12, 10, -9, 14, 13, -14, -11, -2, -16, -14};
vector<int> addy{15, 10, 2, 16, 12, 11, 5, 16, 6, 15, 3, 12, 10, 13};

vector<int> digits{9, 8, 7, 6, 5, 4, 3, 2, 1};
set<pair<int, int>> z_depth;

int64_t generate(int z, int64_t num, int depth) {
    if (z_depth.contains({z, depth}) || depth == 14) {
        return numeric_limits<int64_t>::max();
    }

    num = num * 10;

    int orz = z;
    for (int i = 0; i < digits.size(); i++) {
        z = orz;

        int w = digits[i];
        int x = z;

        x = x % 26;
        z = z / divs[depth];
        x = x + addx[depth];
        x = x == w ? 1 : 0;
        x = x == 0 ? 1 : 0;

        int y = 25;

        y = y * x;
        y = y + 1;
        z = z * y;
        y = w;
        y = y + addy[depth];
        y = y * x;
        z = z + y;

        if (z == 0 && depth == 13) {
            return num + digits[i];
        }

        int64_t ans = generate(z, num + digits[i], depth + 1);

        if (ans != numeric_limits<int64_t>::max()) {
            return ans;
        }
    }

    z_depth.insert({orz, depth});
    return numeric_limits<int64_t>::max();
}

int main() {
    cout << generate(0, 0, 0) << endl;
}