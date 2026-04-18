class Solution {
public:
    int mirrorDistance(int n) {
        int r = 0, x = n;
        while (x) {
            r = r * 10 + x % 10;
            x /= 10;
        }
        return abs(n - r);
    }
};