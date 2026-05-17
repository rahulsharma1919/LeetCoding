class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            if (arr[i] == 0)
                return true;
            for (int nxt : {i + arr[i], i - arr[i]})
                if (nxt >= 0 && nxt < n && !visited[nxt]) {
                    visited[nxt] = true;
                    q.push(nxt);
                }
        }
        return false;
    }
};