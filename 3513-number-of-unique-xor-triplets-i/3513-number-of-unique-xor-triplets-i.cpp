class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return 1;
        if (n == 2)
            return 2;
        // For n>=3, all values 0..2^k-1 are reachable where 2^k > n
        int p = 1;
        while (p <= n)
            p <<= 1;
        return p;
    }
};