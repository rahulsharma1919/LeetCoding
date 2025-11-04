class Solution {
public:
    vector<int> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<int> ans;

        for (int i = 0; i + k <= n; i++) {
            unordered_map<int, int> freq;
            for (int j = i; j < i + k; j++)
                freq[nums[j]]++;

            vector<pair<int, int>> v;
            for (auto& p : freq)
                v.push_back({p.second, p.first});

            sort(v.begin(), v.end(), [](auto& a, auto& b) {
                if (a.first == b.first)
                    return a.second > b.second;
                return a.first > b.first;
            });

            int sum = 0, count = 0;
            for (auto& p : v) {
                if (count == x)
                    break;
                sum += p.first * p.second;
                count++;
            }
            ans.push_back(sum);
        }

        return ans;
    }
};
