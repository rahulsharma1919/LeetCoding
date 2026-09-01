class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();

        vector<pair<int, int>> litterPos;
        int sr = -1, sc = -1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'L') {
                    litterPos.push_back({i, j});
                } else if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
            }
        }

        int L = litterPos.size();
        int fullMask = (1 << L) - 1;

        // map (r,c) -> litter index, for quick mask updates
        vector<vector<int>> litterIdx(m, vector<int>(n, -1));
        for (int idx = 0; idx < L; idx++) {
            litterIdx[litterPos[idx].first][litterPos[idx].second] = idx;
        }

        // visited[r][c][e][mask]
        vector<vector<vector<vector<bool>>>> visited(
            m, vector<vector<vector<bool>>>(
                   n, vector<vector<bool>>(energy + 1,
                                           vector<bool>(1 << L, false))));

        int startMask = 0;
        if (litterIdx[sr][sc] != -1)
            startMask |= (1 << litterIdx[sr][sc]);

        queue<tuple<int, int, int, int, int>> q; // r, c, e, mask, dist
        q.push({sr, sc, energy, startMask, 0});
        visited[sr][sc][energy][startMask] = true;

        if (startMask == fullMask)
            return 0;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c, e, mask, dist] = q.front();
            q.pop();

            if (e == 0)
                continue;

            for (int dir = 0; dir < 4; dir++) {
                int nr = r + dr[dir], nc = c + dc[dir];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;
                if (classroom[nr][nc] == 'X')
                    continue;

                int ne = e - 1;
                if (classroom[nr][nc] == 'R')
                    ne = energy; // reset

                int nmask = mask;
                if (litterIdx[nr][nc] != -1)
                    nmask |= (1 << litterIdx[nr][nc]);

                if (!visited[nr][nc][ne][nmask]) {
                    visited[nr][nc][ne][nmask] = true;
                    if (nmask == fullMask)
                        return dist + 1;
                    q.push({nr, nc, ne, nmask, dist + 1});
                }
            }
        }

        return -1;
    }
};