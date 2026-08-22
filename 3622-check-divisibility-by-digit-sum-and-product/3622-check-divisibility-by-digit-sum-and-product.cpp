class Solution {
public:
    bool checkDivisibility(int n) {
        int sum = 0, product = 1;
        int num = n;

        while (num > 0) {
            int digit = num % 10;
            sum += digit;
            product *= digit;
            num /= 10;
        }

        return n % (sum + product) == 0;
    }
};