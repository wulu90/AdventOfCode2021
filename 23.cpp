#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/**
 * #############
 * #...........#
 * ###D#A#C#D###
 *   #D#C#B#A#
 *   #D#B#A#C#
 *   #C#A#B#B#
 *   #########
 */

vector<int> allres;

struct state {
    array<char, 11> hallway;
    array<array<char, 4>, 4> siderooms;

    // array<char,91>

    int energy;

    state* parent;
    vector<unique_ptr<state>> children;

    state() = default;

    state(state* s) {
        hallway   = s->hallway;
        siderooms = s->siderooms;
        energy    = s->energy;
    }
};

bool is_done(const array<array<char, 4>, 4>& siderooms) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (siderooms[i][j] != 'A' + i) {
                return false;
            }
        }
    }
    return true;
}

bool need_to_out_room(const array<array<char, 4>, 4>& siderooms, int sideroomindex) {
    for (int i = 0; i < 4; i++) {
        if (siderooms[sideroomindex][i] != '.' && siderooms[sideroomindex][i] != 'A' + sideroomindex) {
            return true;
        }
    }
    return false;
}

vector<int> find_hallway_blank_poss(const array<char, 11>& hallway, int sideroomindex) {
    vector<int> hallwal_all{0, 1, 3, 5, 7, 9, 10};

    vector<int> res;

    auto it = upper_bound(hallwal_all.begin(), hallwal_all.end(), (sideroomindex + 1) * 2);
    int mid = it - hallwal_all.begin();

    for (auto i = it - 1; i >= hallwal_all.begin(); i--) {
        if (hallway[*i] != '.') {
            break;
        } else {
            res.push_back(*i);
        }
    }

    for (auto i = it; i != hallwal_all.end(); i++) {
        if (hallway[*i] != '.') {
            break;
        } else {
            res.push_back(*i);
        }
    }

    return res;
}

bool room_empty(const array<array<char, 4>, 4>& siderooms, char amphipod) {
    size_t inx = amphipod - 'A';
    if (siderooms[inx][0] == '.' && siderooms[inx][1] == '.' && siderooms[inx][2] == '.' && siderooms[inx][3] == '.') {
        return true;
    } else
        return false;
}

bool room_only(const array<array<char, 4>, 4>& siderooms, char amphipod) {
    size_t inx = amphipod - 'A';

    for (size_t i = 0; i < 4; i++) {
        if (!(siderooms[inx][i] == '.' || siderooms[inx][i] == amphipod)) {
            return false;
        }
    }
    return true;
}

bool room_clear(const array<array<char, 4>, 4>& siderooms, char amphipod) {
    if (room_empty(siderooms, amphipod) || room_only(siderooms, amphipod)) {
        return true;
    } else
        return false;
}

bool room_to_room(const array<char, 11>& hallway, const array<array<char, 4>, 4>& siderooms, int sideroomindex) {
    if (room_clear(siderooms, 'A' + sideroomindex)) {
        return false;
    }

    char amp = 'a';

    for (int i = 0; i < 4; i++) {
        if (siderooms[sideroomindex][i] != '.') {
            amp = siderooms[sideroomindex][i];
            break;
        }
    }

    if (amp == 'a')
        return false;

    int to_index = amp - 'A';

    if (room_clear(siderooms, amp)) {
        // find if hallway block;

        int start = sideroomindex < to_index ? sideroomindex : to_index;
        int end   = sideroomindex < to_index ? to_index : sideroomindex;
        start     = (start + 1) * 2;
        end       = (end + 1) * 2;
        for (int i = start; i < end; i++) {
            if (hallway[i] != '.') {
                return false;
            }
        }
    } else {
        return false;
    }

    return true;
}

bool hallway_to_room(const array<char, 11>& hallway, const array<array<char, 4>, 4>& siderooms, int index) {
    // 0,1,3,5,7,9,10
    // 2,4,6,8

    int room_pos = (hallway[index] - 'A') * 2 + 2;

    int start = index < room_pos ? index + 1 : room_pos;
    int end   = index < room_pos ? room_pos : index;

    for (int i = start; i < end; i++) {
        if (hallway[i] != '.') {
            return false;
        }
    }

    if (room_clear(siderooms, hallway[index])) {
        return true;
    } else
        return false;
}

int find_empty_in_room(const array<array<char, 4>, 4>& siderooms, int index) {
    int emptycount = 0;
    for (int i = 0; i < 4; i++) {
        if (siderooms[index][i] == '.') {
            emptycount += 1;
        } else {
            break;
        }
    }
    return emptycount - 1;
}

void next(state* s) {
    if (is_done(s->siderooms)) {
        // cout << s->energy << endl;
        allres.push_back(s->energy);
        return;
    }

    // from room to hallway
    for (int i = 0; i < 4; i++) {
        if (need_to_out_room(s->siderooms, i)) {
            auto hp = find_hallway_blank_poss(s->hallway, i);
            if (hp.size() > 0) {
                for (int j = 0; j < 4; j++) {
                    if (s->siderooms[i][j] != '.') {
                        for (auto c : hp) {
                            auto child = make_unique<state>(s);

                            child->hallway[c]      = s->siderooms[i][j];
                            child->siderooms[i][j] = '.';
                            child->energy += (abs((i + 1) * 2 - c) + 1 + j) * pow(10, s->siderooms[i][j] - 'A');
                            child->parent = s;
                            s->children.push_back(move(child));
                        }
                        break;    // just find one top amp
                    }
                }
            }
        }
    }

    // hallway to room
    for (int i = 0; i < 11; i++) {
        if (s->hallway[i] != '.') {
            if (hallway_to_room(s->hallway, s->siderooms, i)) {
                auto child = make_unique<state>(s);

                int roomindex = s->hallway[i] - 'A';
                int k         = find_empty_in_room(s->siderooms, roomindex);

                child->hallway[i] = '.';

                child->siderooms[roomindex][k] = s->hallway[i];
                child->energy += (abs(i - (roomindex + 1) * 2) + k + 1) * pow(10, roomindex);

                s->children.push_back(move(child));
            }
        }
    }

    // room to room
    for (int i = 0; i < 4; i++) {
        if (room_to_room(s->hallway, s->siderooms, i)) {
            auto child = make_unique<state>(s);

            int k = 0;
            for (int j = 0; j < 4; j++) {
                if (s->siderooms[i][j] != '.') {
                    k = j;
                    break;
                }
            }

            int toroom = s->siderooms[i][k] - 'A';
            int to     = find_empty_in_room(s->siderooms, toroom);

            child->siderooms[i][k]       = '.';
            child->siderooms[toroom][to] = 'A' + toroom;
            child->energy += ((abs(i - toroom)) * 2 + 1 + k + to + 1) * pow(10, toroom);

            s->children.push_back(move(child));
        }
    }

    for (int i = 0; i < s->children.size(); i++) {
        next(s->children[i].get());
    }
}

int main() {
    state s;
    s.hallway   = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'};
    s.siderooms = {{{'D', 'D', 'D', 'C'}, {'A', 'C', 'B', 'A'}, {'C', 'B', 'A', 'B'}, {'D', 'A', 'C', 'B'}}};
    s.energy    = 0;

    next(&s);

    cout << *min_element(allres.begin(), allres.end()) << endl;
}