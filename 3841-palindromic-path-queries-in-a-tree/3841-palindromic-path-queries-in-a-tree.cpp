class Solution {
public:
    int n, timer;
    vector<vector<int>> adj;
    vector<int> par, dep, heavy, head, pos, sz;
    vector<int> bit; // Fenwick over XOR masks on HLD positions

    void upd(int i, int v) {
        for (i++; i <= n; i += i & -i)
            bit[i] ^= v;
    }
    int pre(int i) {
        int r = 0;
        for (i++; i > 0; i -= i & -i)
            r ^= bit[i];
        return r;
    }
    int rangeXor(int l, int r) { return pre(r) ^ (l ? pre(l - 1) : 0); }

    vector<bool> palindromePath(int N, vector<vector<int>>& edges, string s,
                                vector<string>& queries) {
        n = N;
        adj.assign(n, {});
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        par.assign(n, -1);
        dep.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        sz.assign(n, 1);

        // iterative DFS order to compute parent, depth, subtree size
        vector<int> order;
        order.reserve(n);
        vector<int> st = {0};
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);
            for (int v : adj[u])
                if (v != par[u]) {
                    par[v] = u;
                    dep[v] = dep[u] + 1;
                    st.push_back(v);
                }
        }
        for (int i = n - 1; i > 0; i--) {
            int u = order[i];
            sz[par[u]] += sz[u];
        }
        for (int u : order) {
            int best = -1;
            for (int v : adj[u])
                if (v != par[u] && (best == -1 || sz[v] > sz[best]))
                    best = v;
            heavy[u] = best;
        }
        // assign head and positions so each heavy chain is contiguous
        timer = 0;
        for (int u : order) {
            if (par[u] == -1 || heavy[par[u]] != u) {
                for (int v = u; v != -1; v = heavy[v]) {
                    head[v] = u;
                    pos[v] = timer++;
                }
            }
        }

        bit.assign(n + 1, 0);
        for (int i = 0; i < n; i++)
            upd(pos[i], 1 << (s[i] - 'a'));

        auto pathXor = [&](int a, int b) {
            int r = 0;
            while (head[a] != head[b]) {
                if (dep[head[a]] < dep[head[b]])
                    swap(a, b);
                r ^= rangeXor(pos[head[a]], pos[a]);
                a = par[head[a]];
            }
            if (dep[a] > dep[b])
                swap(a, b);
            r ^= rangeXor(pos[a], pos[b]);
            return r;
        };

        vector<bool> ans;
        for (auto& q : queries) {
            stringstream ss(q);
            string type, x, y;
            ss >> type >> x >> y;
            if (type == "update") {
                int u = stoi(x);
                upd(pos[u], (1 << (s[u] - 'a')) ^ (1 << (y[0] - 'a')));
                s[u] = y[0];
            } else {
                int m = pathXor(stoi(x), stoi(y));
                ans.push_back((m & (m - 1)) ==
                              0); // at most one odd-count letter
            }
        }
        return ans;
    }
};