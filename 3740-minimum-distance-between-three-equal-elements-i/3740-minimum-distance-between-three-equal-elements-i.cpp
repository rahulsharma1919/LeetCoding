class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        unordered_map<int, vector<int>> idx;
        for (int i = 0; i < nums.size(); i++)
            idx[nums[i]].push_back(i);

        int ans = INT_MAX;
        for (auto& [v, positions] : idx) {
            if (positions.size() < 3)
                continue;
            for (int i = 0; i + 2 < positions.size(); i++) {
                int a = positions[i], b = positions[i + 1],
                    c = positions[i + 2];
                ans = min(ans, 2 * (c - a));
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};