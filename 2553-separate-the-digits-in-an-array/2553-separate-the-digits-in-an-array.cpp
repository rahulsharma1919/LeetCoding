class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> ans;
        for (int v : nums) {
            string s = to_string(v);
            for (char c : s)
                ans.push_back(c - '0');
        }
        return ans;
    }
};