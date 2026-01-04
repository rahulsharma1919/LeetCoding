class Solution {
public:
    bool isPrime(int x) {
        if (x < 2)
            return false;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0)
                return false;
        }
        return true;
    }
    int sumFourDivisors(vector<int>& nums) {
        int ans = 0;
        for (int x : nums) {
            int sum = 0;
            bool found = false;
            // Case 1: x = p^3
            int p = round(pow(x, 1.0 / 3));
            if (1LL * p * p * p == x && isPrime(p)) {
                sum = 1 + p + p * p + x;
                found = true;
            }
            // Case 2: x = p * q (p != q)
            if (!found) {
                for (int i = 2; i * i <= x; i++) {
                    if (x % i == 0) {
                        int j = x / i;
                        if (i != j && isPrime(i) && isPrime(j)) {
                            sum = 1 + i + j + x;
                        }
                        break;
                    }
                }
            }
            ans += sum;
        }
        return ans;
    }
};
