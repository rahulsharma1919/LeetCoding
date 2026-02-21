class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        int mask = 665772; // primes up to 20
        int ans = 0;

        for (int x = left; x <= right; x++) {
            if ((mask >> __builtin_popcount(x)) & 1)
                ans++;
        }
        return ans;
    }
};