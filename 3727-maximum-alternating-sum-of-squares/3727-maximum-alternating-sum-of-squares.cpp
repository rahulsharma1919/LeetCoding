class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> sq(n);
        for (int i = 0; i < n; i++)
            sq[i] = abs(nums[i]);
        sort(sq.begin(), sq.end());

        long long sum = 0;
        int minus = n / 2; // positions with a minus sign
        for (int i = 0; i < n; i++) {
            long long v = (long long)sq[i] * sq[i];
            sum += (i < minus) ? -v : v; // smallest squares get subtracted
        }
        return sum;
    }
};