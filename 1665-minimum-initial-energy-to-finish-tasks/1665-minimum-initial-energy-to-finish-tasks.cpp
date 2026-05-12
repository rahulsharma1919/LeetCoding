class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(),
             [](auto& a, auto& b) { return (a[1] - a[0]) > (b[1] - b[0]); });

        int ans = 0, spent = 0;
        for (auto& t : tasks) {
            ans = max(ans, spent + t[1]);
            spent += t[0];
        }
        return ans;
    }
};