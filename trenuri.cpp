#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

void topologicalSort(int v,
    const vector<vector<int>>& adj, vector<bool>& visited, stack<int>& stack) {

    visited[v] = true;
    for (int i : adj[v]) {
        if (!visited[i]) {
            topologicalSort(i, adj, visited, stack);
        }
    }
    stack.push(v);
}

int maxPathCities(const string& start, const string& end,
    vector<vector<int>>& adj, unordered_map<string, int>& indices) {

    int n = adj.size();
    vector<bool> visited(n, false);
    stack<int> stack;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            topologicalSort(i, adj, visited, stack);
        }
    }

    vector<int> dist(n, 0);
    dist[indices[start]] = 1;

    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();
        if (dist[u] != 0) {
            for (int i : adj[u]) {
                if (dist[u] + 1 > dist[i]) {
                    dist[i] = dist[u] + 1;
                }
            }
        }
    }
    return dist[indices[end]];
}

int main() {
    ifstream fin("trenuri.in");
    ofstream fout("trenuri.out");

    string start, end;
    fin >> start >> end;

    int M;
    fin >> M;
    unordered_map<string, int> indices;
    vector<vector<int>> adj;
    int index = 0;

    for (int i = 0; i < M; i++) {
        string x, y;
        fin >> x >> y;
        if (indices.find(x) == indices.end()) {
            indices[x] = index++;
            adj.push_back(vector<int>());
        }
        if (indices.find(y) == indices.end()) {
            indices[y] = index++;
            adj.push_back(vector<int>());
        }
        adj[indices[x]].push_back(indices[y]);
    }

    fout << maxPathCities(start, end, adj, indices) << endl;
    fin.close();
    fout.close();
    return 0;
}
