class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        vector<int> freq(100001, 0);
        for (int c : costs)
            freq[c]++;

        int ans = 0;
        for (int price = 1; price <= 100000 && coins >= price; price++) {
            int buy = min(freq[price], coins / price);
            ans += buy;
            coins -= buy * price;
        }
        return ans;
    }
};