class Solution {
public:
    int smallestRepunitDivByK(int k) {
        if (k % 2 == 0 || k % 5 == 0)
            return -1;

        vector<bool> seen(k, false);
        int rem = 0;

        for (int len = 1; len <= k; len++) {
            rem = (rem * 10 + 1) % k;
            if (rem == 0)
                return len;
            if (seen[rem])
                return -1;
            seen[rem] = true;
        }

        return -1;
    }
};
