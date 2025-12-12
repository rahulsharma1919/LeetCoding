class Solution {
public:
    vector<int> countMentions(int numberOfUsers,
                              vector<vector<string>>& events) {
        vector<int> mentions(numberOfUsers, 0);
        const int INF = 1e9;

        vector<int> offlineUntil(numberOfUsers, 0);
        vector<bool> online(numberOfUsers, true);
        unordered_map<int, vector<vector<string>>> byTime;
        byTime.reserve(events.size() * 2);
        vector<int> times;
        times.reserve(events.size());
        for (auto& e : events) {
            int t = stoi(e[1]);
            if (byTime.find(t) == byTime.end())
                times.push_back(t);
            byTime[t].push_back(e);
        }
        sort(times.begin(), times.end());
        times.erase(unique(times.begin(), times.end()), times.end());

        for (int t : times) {
            for (int u = 0; u < numberOfUsers; ++u) {
                if (!online[u] && offlineUntil[u] <= t) {
                    online[u] = true;
                }
            }

            for (auto& ev : byTime[t]) {
                if (ev[0] == "OFFLINE") {
                    int u = stoi(ev[2]);
                    online[u] = false;
                    offlineUntil[u] = t + 60;
                }
            }

            for (auto& ev : byTime[t]) {
                if (ev[0] != "MESSAGE")
                    continue;
                string msg = ev[2];

                if (msg == "ALL") {
                    for (int u = 0; u < numberOfUsers; ++u)
                        mentions[u]++;
                } else if (msg == "HERE") {
                    for (int u = 0; u < numberOfUsers; ++u)
                        if (online[u])
                            mentions[u]++;
                } else {
                    stringstream ss(msg);
                    string token;
                    while (ss >> token) {
                        if (token.size() >= 3 && token.rfind("id", 0) == 0) {
                            int u = stoi(token.substr(2));
                            mentions[u]++;
                        }
                    }
                }
            }
        }

        return mentions;
    }
};
