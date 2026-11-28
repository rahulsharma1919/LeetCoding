class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> cntF(n + 1, 0);
        for (auto& it : items)
            cntF[it[0]]++;

        // mult[f] = number of items whose factor is a multiple of f
        vector<int> mult(n + 1, 0);
        for (int f = 1; f <= n; f++)
            for (int m = f; m <= n; m += f)
                mult[f] += cntF[m];

        long long pm = LLONG_MAX;
        for (auto& it : items)
            pm = min(pm, (long long)it[1]);

        // groups: (price, d) where d = number of free-eligible partners
        vector<pair<long long, long long>> g;
        for (auto& it : items) {
            long long d = mult[it[0]] - 1;
            if (d > 0 && (long long)it[1] < 2 * pm)
                g.push_back({it[1], d});
        }
        sort(g.begin(), g.end());

        long long R = budget, k = 0;
        for (auto& [p, d] : g) {
            long long t = min(d, R / p);
            k += t;
            R -= t * p;
            if (t < d)
                break; // can't afford a full group, later ones cost at least as
                       // much
        }
        return (int)(2 * k + R / pm);
    }
};