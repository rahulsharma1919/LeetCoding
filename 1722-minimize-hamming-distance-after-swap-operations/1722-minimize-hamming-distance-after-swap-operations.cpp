class Solution {
public:
    vector<int> p;
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }

    int minimumHammingDistance(vector<int>& source, vector<int>& target,
                               vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        p.resize(n);
        iota(p.begin(), p.end(), 0);

        for (auto& s : allowedSwaps) {
            int a = find(s[0]), b = find(s[1]);
            if (a != b)
                p[a] = b;
        }

        unordered_map<int, unordered_map<int, int>> groups;
        for (int i = 0; i < n; i++)
            groups[find(i)][source[i]]++;

        int ans = 0;
        for (int i = 0; i < n; i++) {
            int root = find(i);
            if (groups[root].count(target[i]) && groups[root][target[i]] > 0)
                groups[root][target[i]]--;
            else
                ans++;
        }

        return ans;
    }
};