class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        double totalArea = 0;
        double low = 1e18, high = 0;
        for (auto& s : squares) {
            double y = s[1], l = s[2];
            totalArea += l * l;
            low = min(low, y);
            high = max(high, y + l);
        }
        double target = totalArea / 2.0;

        for (int iter = 0; iter < 80; iter++) {
            double mid = (low + high) / 2.0;
            double below = 0;
            for (auto& s : squares) {
                double y = s[1], l = s[2];
                double h = mid - y;
                if (h > 0) {
                    below += l * min(h, l);
                }
            }
            if (below < target)
                low = mid;
            else
                high = mid;
        }
        return low;
    }
};
