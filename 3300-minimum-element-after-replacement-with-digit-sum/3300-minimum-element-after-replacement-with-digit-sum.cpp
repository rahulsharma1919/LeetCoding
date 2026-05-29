class Solution {
public:
    int minElement(vector<int>& nums) {
        int minVal = INT_MAX;
        for (int n : nums) {
            int sum = 0;
            while (n > 0) {
                sum += n % 10;
                n /= 10;
            }
            minVal = min(minVal, sum);
        }
        return minVal;
    }
};