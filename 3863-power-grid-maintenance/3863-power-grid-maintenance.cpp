#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }
    int find(int x) {
        if (x == parent[x])
            return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return;
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
};

class Solution {
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections,
                               vector<vector<int>>& queries) {
        DSU dsu(c);

        for (auto& edge : connections)
            dsu.unite(edge[0], edge[1]);

        unordered_map<int, set<int>> gridOnline;
        for (int i = 1; i <= c; i++) {
            int root = dsu.find(i);
            gridOnline[root].insert(i);
        }

        vector<bool> online(c + 1, true);
        vector<int> ans;

        for (auto& q : queries) {
            int type = q[0], x = q[1];
            int root = dsu.find(x);

            if (type == 1) {
                if (online[x])
                    ans.push_back(x);
                else {
                    if (gridOnline[root].empty())
                        ans.push_back(-1);
                    else
                        ans.push_back(*gridOnline[root].begin());
                }
            } else if (type == 2) {
                if (online[x]) {
                    online[x] = false;
                    gridOnline[root].erase(x);
                }
            }
        }

        return ans;
    }
};
