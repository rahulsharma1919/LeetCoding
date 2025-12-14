class Solution {
public:
    int numberOfWays(string corridor) {
        const int MOD = 1e9 + 7;
        long long ans = 1;

        int seatCount = 0;
        int plantCount = 0;
        bool betweenPairs = false;

        for (char c : corridor) {
            if (c == 'S') {
                seatCount++;
                if (seatCount > 2 && seatCount % 2 == 1) {
                    ans = (ans * (plantCount + 1)) % MOD;
                    plantCount = 0;
                }
            } else if (seatCount >= 2 && seatCount % 2 == 0) {
                plantCount++;
            }
        }

        if (seatCount == 0 || seatCount % 2 != 0)
            return 0;

        return ans;
    }
};
