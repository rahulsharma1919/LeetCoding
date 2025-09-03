class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        int n = points.size();
        if (n < 2) return 0;

        // sort by x asc; for equal x, y desc
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) return a[0] < b[0];
            return a[1] > b[1];
        });

        int ans = 0;

        // Fix A at i, scan candidate B at j > i
        for (int i = 0; i < n - 1; ++i) {
            const auto& A = points[i];

            // Bounds that candidates must strictly lie within
            // Start so first candidate must satisfy x >= A.x and y <= A.y
            long long xMin = (long long)A[0] - 1;     // require x > xMin  => x >= A.x
            long long xMax = LLONG_MAX;               // no upper x limit
            long long yMin = LLONG_MIN;               // no lower y limit initially
            long long yMax = (long long)A[1] + 1;     // require y < yMax  => y <= A.y

            for (int j = i + 1; j < n; ++j) {
                const auto& B = points[j];
                long long x = B[0], y = B[1];
                // strict inequalities ensure "no other point on border/in interior"
                if (x > xMin && x < xMax && y > yMin && y < yMax) {
                    // valid pair (A,B)
                    ++ans;
                    // update lower bounds: any future candidate must be strictly to the right
                    // and strictly above this B's y (so previous point won't lie inside new rectangle)
                    xMin = x;
                    yMin = y;
                }
            }
        }

        return ans;
    }
};
