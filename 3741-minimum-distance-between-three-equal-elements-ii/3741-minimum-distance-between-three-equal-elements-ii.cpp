class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        unordered_map<int, vector<int>> idx;
        for (int i = 0; i < (int)nums.size(); i++)
            idx[nums[i]].push_back(i);

        int ans = INT_MAX;
        for (auto& [v, pos] : idx) {
            if (pos.size() < 3)
                continue;
            for (int i = 0; i + 2 < (int)pos.size(); i++)
                ans = min(ans, 2 * (pos[i + 2] - pos[i]));
        }
        return ans == INT_MAX ? -1 : ans;
    }
};