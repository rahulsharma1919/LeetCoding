class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<long long> ans(n, 0);
        unordered_map<int, vector<int>> idx;

        for (int i = 0; i < n; i++)
            idx[nums[i]].push_back(i);

        for (auto& [v, pos] : idx) {
            int m = pos.size();
            vector<long long> pre(m + 1, 0);
            for (int i = 0; i < m; i++)
                pre[i + 1] = pre[i] + pos[i];

            for (int i = 0; i < m; i++) {
                long long left = (long long)i * pos[i] - pre[i];
                long long right =
                    (pre[m] - pre[i + 1]) - (long long)(m - i - 1) * pos[i];
                ans[pos[i]] = left + right;
            }
        }

        return ans;
    }
};