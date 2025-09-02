class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        int n = points.size();
        int count = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                auto A = points[i];
                auto B = points[j];
                
                // Check if A is upper-left of B
                if (A[0] <= B[0] && A[1] >= B[1]) {
                    bool valid = true;
                    for (int k = 0; k < n; k++) {
                        if (k == i || k == j) continue;
                        auto P = points[k];
                        if (A[0] <= P[0] && P[0] <= B[0] &&
                            B[1] <= P[1] && P[1] <= A[1]) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) count++;
                }
            }
        }
        
        return count;
    }
};
