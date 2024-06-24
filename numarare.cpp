#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>

#define MOD 1000000007

using namespace std;

vector<vector<int>> read_graph(int M, ifstream& fin) {
    vector<vector<int>> graph;
    int x, y;
    for (int i = 0; i < M; ++i) {
        fin >> x >> y;
        while (graph.size() <= max(x, y)) {
            graph.push_back(vector<int>());
        }
        graph[x - 1].push_back(y - 1);
    }
    return graph;
}

vector<vector<int>> intersect_graphs(const vector<vector<int>>& g1,
                                    const vector<vector<int>>& g2) {
    int num_nodes = max(g1.size(), g2.size());
    vector<vector<int>> common(num_nodes);
    for (int i = 0; i < num_nodes; i++) {
        unordered_set<int> common_edges;
        if (g1.size() > i) {
            for (int edge : g1[i]) {
                common_edges.insert(edge);
            }
        }
        if (g2.size() > i) {
            vector<int> temp;
            for (int edge : g2[i]) {
                if (common_edges.find(edge) != common_edges.end()) {
                    temp.push_back(edge);
                }
            }
            common[i] = temp;
        }
    }
    return common;
}

int count_common_paths(int N, const vector<vector<int>>& graph) {
    vector<int> dp(N, 0);
    dp[0] = 1;
    queue<int> process;
    vector<int> in_degree(N, 0);

    for (int i = 0; i < graph.size(); ++i) {
        for (int neighbor : graph[i]) {
            ++in_degree[neighbor];
        }
    }

    for (int i = 0; i < N; ++i) {
        if (in_degree[i] == 0) {
            process.push(i);
        }
    }

    while (!process.empty()) {
        int node = process.front();
        process.pop();
        for (int neighbor : graph[node]) {
            dp[neighbor] = (dp[neighbor] + dp[node]) % MOD;
            --in_degree[neighbor];
            if (in_degree[neighbor] == 0) {
                process.push(neighbor);
            }
        }
    }
    return dp[N - 1];
}

int main() {
    ifstream fin("numarare.in");
    ofstream fout("numarare.out");

    int N, M;
    fin >> N >> M;

    vector<vector<int>> graph1 = read_graph(M, fin);
    vector<vector<int>> graph2 = read_graph(M, fin);

    vector<vector<int>> common_graph = intersect_graphs(graph1, graph2);

    int result = count_common_paths(N, common_graph);

    fout << result;
    return 0;
}
