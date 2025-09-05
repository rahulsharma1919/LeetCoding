class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        for (int k = 1; k <= 60; k++) {
            long long remain = (long long)num1 - (long long)k * num2;
            if (remain < k) continue; // can't split into k positive powers of 2
            
            int bits = __builtin_popcountll(remain); // number of set bits
            if (bits <= k) return k;
        }
        return -1;
    }
};
