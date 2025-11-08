class Solution {
public:
    int minimumOneBitOperations(int n) {
        if (n == 0)
            return 0;
        int k = 31 - __builtin_clz(n);
        return ((1 << (k + 1)) - 1) - minimumOneBitOperations(n ^ (1 << k));
    }
};
