class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        int n = points.size();
        int ans = 0;
        
        for (int i = 0; i < n; ++i) {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                int x2 = points[j][0], y2 = points[j][1];
                
                // A is on the "upper-left side" of B:
                // allow same x or same y (line is allowed), but they must be different points
                if (x1 <= x2 && y1 >= y2) {
                    bool valid = true;
                    // Check every other point: it must NOT lie inside or on the border
                    for (int k = 0; k < n; ++k) {
                        if (k == i || k == j) continue;
                        int x = points[k][0], y = points[k][1];
                        if (x1 <= x && x <= x2 && y2 <= y && y <= y1) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) ++ans;
                }
            }
        }
        
        return ans;
    }
};
