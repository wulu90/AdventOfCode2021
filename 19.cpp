#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

using Int3 = std::array<int, 3>;
std::array<int, 4> cosv{1, 0, -1, 0};    // cos 0 90 180 270
std::array<int, 4> sinv{0, 1, 0, -1};

Int3 operator+(const Int3& a, const Int3 b) {
    return {a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}

Int3 operator-(const Int3& a, const Int3 b) {
    return {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}

// why there has one more brace?
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/compiler-error-c2078
std::array<Int3, 24> rotations{{{0, 0, 0},    {0, 90, 0},   {0, 180, 0},   {0, 270, 0},   {90, 0, 0},    {90, 90, 0},
                                {90, 180, 0}, {90, 270, 0}, {180, 0, 0},   {180, 90, 0},  {180, 180, 0}, {180, 270, 0},
                                {270, 0, 0},  {270, 90, 0}, {270, 180, 0}, {270, 270, 0}, {0, 0, 90},    {90, 0, 90},
                                {180, 0, 90}, {270, 0, 90}, {0, 0, 270},   {90, 0, 270},  {180, 0, 270}, {270, 0, 270}}};

/**
 * @param c origin coordiante
 * @param a roate angle
 */
Int3 rotate(const Int3& c, const Int3& a) {
    int ax = a[0] / 90;
    int ay = a[1] / 90;
    int az = a[2] / 90;
    Int3 rotx{c[0], c[1] * cosv[ax] - c[2] * sinv[ax], c[1] * sinv[ax] + c[2] * cosv[ax]};
    Int3 roty{rotx[0] * cosv[ay] + rotx[2] * sinv[ay], rotx[1], rotx[2] * cosv[ay] - rotx[0] * sinv[ay]};
    Int3 rotz{roty[0] * cosv[az] - roty[1] * sinv[az], roty[0] * sinv[az] + roty[1] * cosv[az], roty[2]};
    return rotz;
}

/**
 * @param b beacon origin coordiante
 * @param a rotate angel
 * @param d distance
 */
Int3 transform(const Int3& b, const Int3& a, const Int3& d) {
    return rotate(b, a) + d;
}

/**
 * @brief 判断两组beacons三维是否有重叠
 * @param beacons_a 第一组三维坐标点
 * @param beacons_b 第er组三维坐标点
 * @param tran_info 存储转换信息 pair.first 旋转角度 pair.second 平移距离
 * @details
 * 在每一个坐标轴旋转角度组合下，将beacons_b的所有点按坐标轴旋转进行变换，得到ratated_b，\n
 * beacons_a中的所有点，rotated_b中的所有点，a-b得到两点三个方向上的距离dist，\n
 * 将dist加回rotated_b中的所有点上，此时判断rotated_b与beacons_a是否有12个以上的重合点。
 *
 */
bool is_overlap(const std::vector<Int3>& beacons_a, const std::vector<Int3>& beacons_b, std::pair<Int3, Int3>& tran_info) {
    std::vector<Int3> rotated_b;
    for (const auto& r : rotations) {
        rotated_b.clear();

        std::transform(beacons_b.begin(), beacons_b.end(), std::back_inserter(rotated_b), [r](const Int3& p) { return rotate(p, r); });
        for (const auto& a : beacons_a) {
            for (const auto& b : rotated_b) {
                Int3 dist = a - b;

                std::set<Int3> set_a(beacons_a.begin(), beacons_a.end());
                std::set<Int3> set_b;

                std::transform(rotated_b.begin(), rotated_b.end(), std::inserter(set_b, set_b.end()),
                               [&dist](Int3& p) { return p + dist; });

                std::set<Int3> tmp;
                std::set_intersection(set_a.begin(), set_a.end(), set_b.begin(), set_b.end(), std::inserter(tmp, tmp.begin()));

                if (tmp.size() >= 12) {
                    tran_info = {r, dist};
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<std::vector<int>> calc_path(const std::vector<std::pair<int, int>>& overlap_sanner_pairs) {
    auto op = overlap_sanner_pairs;

    std::vector<std::vector<int>> result;
    std::vector<int> st;    // stack

    std::vector<int> visited_op;
    std::vector<int> visited_scanners;

    bool find_new_node = false;
    while (visited_op.size() < op.size()) {
        for (int i = 0; i < op.size(); i++) {
            if (std::find(visited_op.begin(), visited_op.end(), i) == visited_op.end()) {
                st.push_back(op[i].first);
                st.push_back(op[i].second);
                visited_scanners.push_back(op[i].first);
                visited_scanners.push_back(op[i].second);
                visited_op.push_back(i);
                break;
            }
        }

        while (!st.empty()) {
            auto t = st.back();

            int next_op = -1;
            for (int i = 0; i < op.size(); i++) {
                if (std::find(visited_op.begin(), visited_op.end(), i) == visited_op.end() && (op[i].first == t || op[i].second == t)) {
                    next_op = i;
                    break;
                }
            }

            if (next_op != -1) {
                int s_id = op[next_op].first == t ? op[next_op].second : op[next_op].first;

                if (std::find(visited_scanners.begin(), visited_scanners.end(), s_id) == visited_scanners.end()) {
                    find_new_node = true;
                    st.push_back(s_id);
                    visited_op.push_back(next_op);
                    visited_scanners.push_back(s_id);
                } else {
                    visited_op.push_back(next_op);    // 图上有环
                }
            } else {
                if (find_new_node) {    // 在路径上有新得节点，且找不到后续节点的情况下，这一条路径走完。
                    result.push_back(st);
                }
                st.pop_back();
                find_new_node = false;
            }
        }
    }

    return result;
}

int main() {
    std::ifstream input("input/input-19");
    std::string line;

    std::vector<std::vector<Int3>> beacon_all;
    std::vector<Int3> beacons;
    while (std::getline(input, line)) {
        if (line.find("---") != std::string::npos) {
            beacons.clear();
        } else if (line.empty()) {
            beacon_all.push_back(beacons);
        } else {
            auto first_comma  = line.find_first_of(',');
            auto second_comma = line.find_last_of(',');
            Int3 c;
            c[0] = std::stoi(line.substr(0, first_comma));
            c[1] = std::stoi(line.substr(first_comma + 1, second_comma - first_comma - 1));
            c[2] = std::stoi(line.substr(second_comma + 1, line.size() - second_comma - 1));
            beacons.push_back(c);
        }
    }

    beacon_all.push_back(beacons);

    std::set<Int3> distict_beacons;
    std::pair<Int3, Int3> tran_info;

    std::vector<std::pair<int, int>> overlap_pairs;
    std::map<std::pair<int, int>, std::pair<Int3, Int3>> tran_map;    // <a,b> <c,d> 由b向a转换，c 旋转角度，d 距离
    for (int i = 0; i < beacon_all.size() - 1; i++) {
        for (int j = i + 1; j < beacon_all.size(); j++) {
            if (is_overlap(beacon_all[i], beacon_all[j], tran_info)) {
                // std::cout << i << " " << j << std::endl;
                overlap_pairs.push_back({i, j});
                tran_map.insert({{i, j}, tran_info});
            }
        }
    }

    // 预先计算 反向转换参数
    for (auto ops : overlap_pairs) {
        is_overlap(beacon_all[ops.second], beacon_all[ops.first], tran_info);
        tran_map.insert({{ops.second, ops.first}, tran_info});
    }

    auto paths = calc_path(overlap_pairs);

    std::vector<std::vector<Int3>> normalized_beacons(beacon_all.size());

    for (auto& path : paths) {
        for (int i = path.size() - 1; i > 0; i--) {
            auto scanner_a_id = path[i - 1];
            auto scanner_b_id = path[i];
            if (tran_map.find({scanner_a_id, scanner_b_id}) != tran_map.end()) {
                tran_info = tran_map[{scanner_a_id, scanner_b_id}];
            } else {    // 由于预先计算了反向转换参数，所以这一步并不会运行到
                is_overlap(beacon_all[scanner_a_id], beacon_all[scanner_b_id], tran_info);
            }

            for (auto& b : beacon_all[scanner_b_id]) {
                beacon_all[scanner_a_id].push_back(transform(b, tran_info.first, tran_info.second));
            }
        }

        for (auto& b : beacon_all[path[0]]) {
            normalized_beacons[path[0]].push_back(b);
        }
    }

    int distinct = 0;
    for (int i = 0; i < beacon_all.size(); i++) {
        if (!normalized_beacons[i].empty()) {
            std::set<Int3> tmp(normalized_beacons[i].begin(), normalized_beacons[i].end());
            distinct += tmp.size();
        }
    }

    std::cout << distinct << std::endl;
}