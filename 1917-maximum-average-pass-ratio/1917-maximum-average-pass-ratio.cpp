class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        // Max heap to always pick the class with maximum gain
        auto cmp = [](const pair<int,int>& a, const pair<int,int>& b) {
            long double gainA = (long double)(a.first + 1) / (a.second + 1) - (long double)a.first / a.second;
            long double gainB = (long double)(b.first + 1) / (b.second + 1) - (long double)b.first / b.second;
            return gainA < gainB; // max heap
        };

        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

        // Push all classes into the heap
        for (auto &c : classes) {
            pq.push({c[0], c[1]});
        }

        // Assign extra students
        while (extraStudents--) {
            auto [pass, total] = pq.top(); pq.pop();
            pq.push({pass + 1, total + 1});
        }

        // Calculate final average ratio
        long double result = 0.0;
        while (!pq.empty()) {
            auto [pass, total] = pq.top(); pq.pop();
            result += (long double)pass / total;
        }

        return (double)result / classes.size();
    }
};
