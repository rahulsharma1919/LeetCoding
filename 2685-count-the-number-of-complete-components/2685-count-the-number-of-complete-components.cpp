class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<int> par(n);
        iota(par.begin(), par.end(), 0);
        function<int(int)> find = [&](int x) {
            return par[x] == x ? x : par[x] = find(par[x]);
        };

        for (auto& e : edges)
            par[find(e[0])] = find(e[1]);

        unordered_map<int, int> verts, edgeCnt;
        for (int i = 0; i < n; i++)
            verts[find(i)]++;
        for (auto& e : edges)
            edgeCnt[find(e[0])]++;

        int ans = 0;
        for (auto& [root, v] : verts)
            if (edgeCnt[root] == v * (v - 1) / 2)
                ans++;
        return ans;
    }
};