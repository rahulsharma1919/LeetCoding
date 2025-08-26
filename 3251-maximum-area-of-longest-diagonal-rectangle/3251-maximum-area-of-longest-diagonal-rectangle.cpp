class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int maxDiagonal = -1; // store squared diagonal
        int maxArea = -1;

        for (auto &rect : dimensions) {
            int l = rect[0];
            int w = rect[1];
            int diagSq = l * l + w * w;
            int area = l * w;

            if (diagSq > maxDiagonal) {
                maxDiagonal = diagSq;
                maxArea = area;
            } else if (diagSq == maxDiagonal) {
                maxArea = max(maxArea, area);
            }
        }

        return maxArea;
    }
};
