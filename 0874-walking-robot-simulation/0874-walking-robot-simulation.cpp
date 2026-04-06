class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        set<pair<int, int>> blocked;
        for (auto& o : obstacles)
            blocked.insert({o[0], o[1]});

        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        int dir = 0, x = 0, y = 0, ans = 0;

        for (int cmd : commands) {
            if (cmd == -1)
                dir = (dir + 1) % 4;
            else if (cmd == -2)
                dir = (dir + 3) % 4;
            else {
                for (int i = 0; i < cmd; i++) {
                    int nx = x + dx[dir], ny = y + dy[dir];
                    if (blocked.count({nx, ny}))
                        break;
                    x = nx;
                    y = ny;
                    ans = max(ans, x * x + y * y);
                }
            }
        }
        return ans;
    }
};