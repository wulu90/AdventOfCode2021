#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <limits>
#include <queue>

using namespace std;

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Algorithm
void djikstra(const vector<vector<int8_t>> &matrix)
{
    // is square, row = col;
    int row = matrix.size();
    // use Djikstra, vertex num is row*row
    int v_num = row * row;

    int32_t inf = numeric_limits<int32_t>::max();

    vector<int32_t> dist(v_num, inf); // current distance from the 0 to the vertex i
    vector<bool> visited(v_num, false);
    dist[0] = 0;
    //visited[0] = true;
    int cur = 0;

    //vector<vector<int8_t>> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (true)
    {
        vector<int32_t> neighbors{cur - row, cur + row, cur - 1, cur + 1};
        for (auto &nei : neighbors)
        {
            if (nei < 0 || nei > v_num - 1 || (cur / row != nei / row && cur % row != nei % row))
                continue;
            if (!visited[nei] && dist[nei] > dist[cur] + matrix[cur / row][cur % row])
            {
                dist[nei] = dist[cur] + matrix[cur / row][cur % row];
            }
        }
        visited[cur] = true;
        if (visited[v_num - 1])
        {
            break;
        }
        else
        {
            int min = inf;
            for (int i = 0; i < v_num; i++)
            {
                if (!visited[i] && dist[i] < min)
                {
                    min = dist[i];
                    cur = i;
                }
            }
        }
    }

    cout << dist[v_num - 1] - matrix[0][0] + matrix[row - 1][row - 1] << endl;
}

void djikstra_priority_queue(const vector<vector<int8_t>> &matrix)
{
    // is square, row = col;
    int row = matrix.size();
    // use Djikstra, vertex num is row*row
    int v_num = row * row;

    int32_t inf = numeric_limits<int32_t>::max();

    vector<int32_t> dist(v_num, inf); // current distance from the 0 to the vertex i
    vector<bool> visited(v_num, false);
    priority_queue<pair<int32_t, int32_t>, vector<pair<int32_t, int32_t>>, greater<pair<int32_t, int32_t>>> pqueue; // distance,vertex_index;
    dist[0] = 0;
    //visited[0] = true;
    int cur = 0;

    //vector<vector<int8_t>> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (true)
    {
        vector<int32_t> neighbors{cur - row, cur + row, cur - 1, cur + 1};
        for (auto &nei : neighbors)
        {
            if (nei < 0 || nei > v_num - 1 || (cur / row != nei / row && cur % row != nei % row))
                continue;
            if (!visited[nei] && dist[nei] > dist[cur] + matrix[cur / row][cur % row])
            {
                dist[nei] = dist[cur] + matrix[cur / row][cur % row];
                pqueue.push({dist[nei], nei});
            }
        }
        visited[cur] = true;

        if (visited[v_num - 1])
        {
            break;
        }
        else
        {
            cur = pqueue.top().second;
            pqueue.pop();
        }
    }

    cout << dist[v_num - 1] - matrix[0][0] + matrix[row - 1][row - 1] << endl;
}

void part1()
{
    ifstream ifs{"input\\input-15"};
    string line;

    vector<vector<int8_t>> matrix;

    while (getline(ifs, line))
    {
        vector<int8_t> line_vec;
        line_vec.reserve(line.size());
        for (auto &c : line)
        {
            line_vec.push_back(c - '0');
        }
        matrix.push_back(line_vec);
    }

    //djikstra(matrix);
    djikstra_priority_queue(matrix);
}

void part2()
{
    ifstream ifs{"input\\input-15"};
    string line;

    vector<vector<int8_t>> matrix;

    while (getline(ifs, line))
    {
        vector<int8_t> line_vec;
        line_vec.reserve(line.size());
        for (auto &c : line)
        {
            line_vec.push_back(c - '0');
        }
        matrix.push_back(line_vec);
    }

    int row = matrix.size();
    vector<vector<int8_t>> full_matrix;
    full_matrix.resize(row * 5);
    for (auto &fm : full_matrix)
    {
        fm.resize(row * 5);
    }

    for (int i = 0; i < row * 5; i++)
    {
        for (int j = 0; j < row * 5; j++)
        {
            int tile_i = i / row;
            int tile_j = j / row;
            int loc_i = i % row;
            int loc_j = j % row;
            int8_t value = matrix[loc_i][loc_j] + tile_i + tile_j;
            int8_t v = value > 9 ? value - 9 : value;
            full_matrix[i][j] = v;
        }
    }

    djikstra_priority_queue(full_matrix);
}

int main()
{
    part1();
    part2();
}
