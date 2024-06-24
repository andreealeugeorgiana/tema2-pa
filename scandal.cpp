#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

#define MAXN 200011

long long n, m;
vector<int> gIn[MAXN], gOut[MAXN];
vector<int> Comp[MAXN], tmp;
bool vis[MAXN];
int ctc[MAXN], col[MAXN];
stack<int> S;

void addImp(int a, int b) {
    a += n; b += n;
    gIn[a].push_back(b);
    gOut[b].push_back(a);
}

void aORb(int a, int b) {
    addImp(-a, b);
    addImp(-b, a);
}

void dfsF(int node) {
    vis[node] = true;
    for (int newNode : gIn[node]) {
        if (!vis[newNode]) dfsF(newNode);
    }
    S.push(node);
}

void dfsB(int node) {
    ctc[node] = ctc[0];
    tmp.push_back(node);
    for (int newNode : gOut[node]) {
        if (!ctc[newNode]) dfsB(newNode);
    }
}

void setCol(int act, int mCol) {
    int inv = (mCol == 1) ? 2 : 1;
    for (int newNode : Comp[act]) {
        col[newNode] = mCol;
        col[-(newNode - n) + n] = inv;
    }
}

int main() {
    freopen("scandal.in", "r", stdin);
    freopen("scandal.out", "w", stdout);

    scanf("%lld %lld", &n, &m);

    for (int i = 0; i < m; ++i) {
        int x, y, op;
        scanf("%d %d %d", &x, &y, &op);
        switch (op) {
            case 0 : aORb(x, y); break;
            case 1 : aORb(x, -y); break;
            case 2 : aORb(-x, y); break;
            case 3 : aORb(-x, -y); break;
        }
    }

    for (int i = 1; i <= 2 * n; ++i) {
        if (!vis[i]) dfsF(i);
    }

    ctc[0] = 0;
    while (!S.empty()) {
        int node = S.top(); S.pop();
        if (!ctc[node]) {
            ++ctc[0];
            tmp.clear();
            dfsB(node);
            Comp[ctc[0]] = tmp;
        }
    }

    for (int i = 1; i <= ctc[0]; ++i) {
        setCol(i, col[Comp[i][0]] ? col[Comp[i][0]] : 1);
    }

    vector<int> result;
    for (int i = n + 1; i <= 2 * n; ++i) {
        if (col[i] == 2) result.push_back(i - n);
    }

    printf("%d\n", (int)result.size());
    for (int i : result) {
        printf("%d\n", i);
    }

    return 0;
}
