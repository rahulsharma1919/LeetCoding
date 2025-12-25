class Solution {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        sort(happiness.begin(), happiness.end(), greater<int>());

        long long ans = 0;
        long long dec = 0;

        for (int i = 0; i < k; i++) {
            long long curr = happiness[i] - dec;
            if (curr <= 0)
                break;
            ans += curr;
            dec++;
        }

        return ans;
    }
};
