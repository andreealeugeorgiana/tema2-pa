#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const long long INF = numeric_limits<long long>::max();

vector<long long> dijkstra(int source,
    const vector<vector<pair<int, int>>>& adj, int n) {
    vector<long long> dist(n + 1, INF);
    priority_queue<pair<long long, int>,
    vector<pair<long long, int>>, greater<>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, cost] : adj[u]) {
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    ifstream fin("drumuri.in");
    ofstream fout("drumuri.out");

    int n, m;
    fin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        fin >> a >> b >> c;
        adj[b].push_back({a, c});
    }

    int x, y, z;
    fin >> x >> y >> z;

    vector<long long> distFromZ = dijkstra(z, adj, n);

    long long costXToZ = distFromZ[x];
    long long costYToZ = distFromZ[y];

    fout << costXToZ + costYToZ << endl;
    return 0;
}
