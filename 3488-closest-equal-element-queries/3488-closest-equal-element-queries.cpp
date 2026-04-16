class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        unordered_map<int, vector<int>> idx;
        for (int i = 0; i < n; i++) idx[nums[i]].push_back(i);

        vector<int> best(n, -1);
        for (auto& [v, pos] : idx) {
            if (pos.size() == 1) continue;
            int m = pos.size();
            for (int i = 0; i < m; i++) {
                int prev = pos[(i - 1 + m) % m];
                int next = pos[(i + 1) % m];
                int cur  = pos[i];
                int d1 = min(abs(cur - prev), n - abs(cur - prev));
                int d2 = min(abs(cur - next), n - abs(cur - next));
                best[cur] = min(d1, d2);
            }
        }

        vector<int> ans;
        for (int q : queries) ans.push_back(best[q]);
        return ans;
    }
};