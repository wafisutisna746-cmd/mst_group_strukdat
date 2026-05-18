#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

bool compare(Edge a, Edge b) {
    return a.w < b.w;
}

class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findSet(int v) {
        if (parent[v] != v)
            parent[v] = findSet(parent[v]);
        return parent[v];
    }

    void unionSet(int a, int b) {
        int rootA = findSet(a);
        int rootB = findSet(b);

        if (rootA != rootB) {
            if (rank[rootA] < rank[rootB])
                parent[rootA] = rootB;
            else if (rank[rootA] > rank[rootB])
                parent[rootB] = rootA;
            else {
                parent[rootB] = rootA;
                rank[rootA]++;
            }
        }
    }
};

//kruskal
int kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compare);

    DSU dsu(V);
    int mst_weight = 0;

    for (auto &e : edges) {
        if (dsu.findSet(e.u) != dsu.findSet(e.v)) {
            mst_weight += e.w;
            dsu.unionSet(e.u, e.v);
        }
    }

    return mst_weight;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<Edge> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    cout << kruskalMST(V, edges) << endl;
    return 0;
}
