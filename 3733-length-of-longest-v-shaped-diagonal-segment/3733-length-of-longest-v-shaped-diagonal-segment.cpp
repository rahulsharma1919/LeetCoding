class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        const int dirs[4][2] = {{1,1},{1,-1},{-1,-1},{-1,1}}; // ↘, ↙, ↖, ↗

        // memo for states (x,y,dir,canTurn) where canTurn∈{0,1}
        // value = longest length starting from NEXT cell (not counting current)
        vector<int> memo(n * m * 4 * 2, -1);
        auto index = [m](int x, int y, int dir, int canTurn) {
            return (((x * m + y) * 4 + dir) * 2 + canTurn);
        };

        function<int(int,int,int,int,int)> dfs = [&](int cx, int cy, int dir, int canTurn, int target) -> int {
            int nx = cx + dirs[dir][0];
            int ny = cy + dirs[dir][1];

            // must stay in-bounds and match the expected target (2 or 0)
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] != target) return 0;

            int key = index(nx, ny, dir, canTurn);
            int &cached = memo[key];
            if (cached != -1) return cached;

            int nextTarget = 2 - target; // toggles 2<->0
            int best = dfs(nx, ny, dir, canTurn, nextTarget); // continue straight

            if (canTurn) {
                int ndir = (dir + 1) % 4; // one clockwise 90° turn
                best = max(best, dfs(nx, ny, ndir, 0, nextTarget));
            }

            return cached = best + 1; // count this next cell
        };

        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    for (int d = 0; d < 4; ++d) {
                        // after a starting 1, next expected is 2; +1 to include the starting 1
                        res = max(res, dfs(i, j, d, 1, 2) + 1);
                    }
                }
            }
        }
        return res;
    }
};
