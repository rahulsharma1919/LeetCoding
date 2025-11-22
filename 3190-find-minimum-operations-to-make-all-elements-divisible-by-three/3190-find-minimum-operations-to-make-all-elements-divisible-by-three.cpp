class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int ops = 0;
        for (int x : nums) {
            int rem = x % 3;
            if (rem == 1)
                ops += 1; // either subtract 1
            else if (rem == 2)
                ops += 1; // or add 1
        }
        return ops;
    }
};
