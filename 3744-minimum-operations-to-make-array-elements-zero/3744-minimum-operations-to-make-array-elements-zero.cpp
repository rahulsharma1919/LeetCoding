class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        // Precompute power of 4 ranges
        vector<long long> pow4;
        pow4.push_back(1);
        while (pow4.back() <= 1e9) {
            pow4.push_back(pow4.back() * 4);
        }
        
        long long result = 0;
        
        for (auto& q : queries) {
            long long l = q[0], r = q[1];
            long long totalCost = 0;
            
            // Go through ranges of [4^(k-1), 4^k - 1]
            for (int k = 1; k < pow4.size(); k++) {
                long long start = pow4[k-1];
                long long end = min((long long)1e9, pow4[k] - 1);
                
                if (r < start || l > end) continue; // no overlap
                
                long long segL = max(l, start);
                long long segR = min(r, end);
                long long count = segR - segL + 1;
                
                totalCost += count * k;
            }
            
            // since 2 numbers can be processed at once
            result += (totalCost + 1) / 2; 
        }
        
        return result;
    }
};
