class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        int m = buildings.size();

        unordered_map<int, vector<int>> rows, cols;
        rows.reserve(m * 2);
        cols.reserve(m * 2);

        for (auto& b : buildings) {
            int x = b[0], y = b[1];
            rows[x].push_back(y);
            cols[y].push_back(x);
        }

        unordered_map<int, pair<int, int>> rowMinMax, colMinMax;
        rowMinMax.reserve(rows.size() * 2);
        colMinMax.reserve(cols.size() * 2);

        // Compute min/max for each row
        for (auto& kv : rows) {
            int x = kv.first;
            auto& vec = kv.second;
            int mn = INT_MAX, mx = INT_MIN;
            for (int y : vec) {
                mn = min(mn, y);
                mx = max(mx, y);
            }
            rowMinMax[x] = {mn, mx};
        }

        // Compute min/max for each column
        for (auto& kv : cols) {
            int y = kv.first;
            auto& vec = kv.second;
            int mn = INT_MAX, mx = INT_MIN;
            for (int x : vec) {
                mn = min(mn, x);
                mx = max(mx, x);
            }
            colMinMax[y] = {mn, mx};
        }

        int ans = 0;

        // Check each building
        for (auto& b : buildings) {
            int x = b[0], y = b[1];

            auto [rowMin, rowMax] = rowMinMax[x];
            auto [colMin, colMax] = colMinMax[y];

            if (rowMin < y && y < rowMax && colMin < x && x < colMax) {
                ans++;
            }
        }

        return ans;
    }
};
