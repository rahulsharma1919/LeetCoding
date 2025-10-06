class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> visited(n, vector<int>(n, 0));
        priority_queue<pair<int, pair<int, int>>,
                       vector<pair<int, pair<int, int>>>, greater<>>
            pq;

        pq.push({grid[0][0], {0, 0}});
        visited[0][0] = 1;
        int ans = 0;
        vector<int> dir = {0, 1, 0, -1, 0};

        while (!pq.empty()) {
            auto [time, pos] = pq.top();
            pq.pop();
            int x = pos.first, y = pos.second;
            ans = max(ans, time);
            if (x == n - 1 && y == n - 1)
                return ans;

            for (int k = 0; k < 4; k++) {
                int nx = x + dir[k];
                int ny = y + dir[k + 1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                    !visited[nx][ny]) {
                    visited[nx][ny] = 1;
                    pq.push({grid[nx][ny], {nx, ny}});
                }
            }
        }
        return ans;
    }
};
