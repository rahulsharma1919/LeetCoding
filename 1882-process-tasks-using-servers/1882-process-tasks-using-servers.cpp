
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        // Available servers: {weight, index}
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            available;

        // Busy servers: {freeTime, weight, index}
        using Server = tuple<long long, int, int>;

        priority_queue<Server, vector<Server>, greater<Server>> busy;

        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);
        long long currentTime = 0;

        for (int j = 0; j < m; j++) {

            // Time must never move backwards.
            currentTime = max(currentTime, (long long)j);

            // Release all servers that have finished.
            while (!busy.empty() && get<0>(busy.top()) <= currentTime) {

                auto [freeTime, weight, index] = busy.top();
                busy.pop();

                available.push({weight, index});
            }

            // If no server is free, advance time.
            if (available.empty()) {
                currentTime = get<0>(busy.top());

                // Release every server available at this time.
                while (!busy.empty() && get<0>(busy.top()) <= currentTime) {

                    auto [freeTime, weight, index] = busy.top();
                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Choose the server with minimum weight,
            // then minimum index.
            auto [weight, index] = available.top();
            available.pop();

            ans[j] = index;

            // Assign the current task.
            busy.push({currentTime + tasks[j], weight, index});
        }

        return ans;
    }
};
