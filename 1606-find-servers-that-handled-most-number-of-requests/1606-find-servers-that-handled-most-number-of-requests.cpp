
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        // Available servers (sorted by index).
        set<int> available;

        // Busy servers: {finishTime, serverIndex}.
        priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                       greater<pair<long long, int>>>
            busy;

        vector<int> count(k, 0);

        // Initially, all servers are available.
        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        for (int i = 0; i < arrival.size(); i++) {

            // Release servers whose requests are completed.
            while (!busy.empty() && busy.top().first <= arrival[i]) {

                int server = busy.top().second;
                busy.pop();

                available.insert(server);
            }

            // If all servers are busy, drop the request.
            if (available.empty()) {
                continue;
            }

            // Preferred server.
            int preferred = i % k;

            // Find the next available server.
            auto it = available.lower_bound(preferred);

            // Wrap around if necessary.
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Assign the request.
            available.erase(it);

            count[server]++;

            // Calculate completion time.
            long long finishTime = 1LL * arrival[i] + load[i];

            busy.push({finishTime, server});
        }

        // Find the maximum number of handled requests.
        int maxRequests = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxRequests) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
