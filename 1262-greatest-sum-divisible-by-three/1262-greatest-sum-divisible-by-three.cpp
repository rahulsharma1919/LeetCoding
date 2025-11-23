class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        vector<int> dp = {0, INT_MIN, INT_MIN};

        for (int x : nums) {
            vector<int> temp = dp;
            for (int i = 0; i < 3; i++) {
                int newMod = (i + x) % 3;
                temp[newMod] = max(temp[newMod], dp[i] + x);
            }
            dp = temp;
        }

        return dp[0];
    }
};
