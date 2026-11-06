
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x,
                             vector<int>& queries) {
        sort(logs.begin(), logs.end(),
             [](const auto& a, const auto& b) { return a[1] < b[1]; });

        int m = queries.size();

        vector<pair<int, int>> sortedQueries;
        for (int i = 0; i < m; i++) {
            sortedQueries.push_back({queries[i], i});
        }

        sort(sortedQueries.begin(), sortedQueries.end());

        vector<int> ans(m);
        vector<int> freq(n + 1, 0);

        int left = 0, right = 0;
        int active = 0;

        for (auto [q, idx] : sortedQueries) {
            int start = q - x;

            // Add logs within the current time window
            while (right < logs.size() && logs[right][1] <= q) {
                int server = logs[right][0];

                if (freq[server] == 0)
                    active++;

                freq[server]++;
                right++;
            }

            // Remove logs that are before the window
            while (left < right && logs[left][1] < start) {
                int server = logs[left][0];

                freq[server]--;

                if (freq[server] == 0)
                    active--;

                left++;
            }

            ans[idx] = n - active;
        }

        return ans;
    }
};
