class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1)
            return 0;

        vector<long long> a(nums.begin(), nums.end());
        vector<int> left(n), right(n);
        vector<bool> alive(n, true);

        for (int i = 0; i < n; i++) {
            left[i] = i - 1;
            right[i] = i + 1;
        }

        auto isBad = [&](int i) {
            return i != -1 && right[i] != n && a[i] > a[right[i]];
        };

        int bad = 0;
        for (int i = 0; i + 1 < n; i++) {
            if (a[i] > a[i + 1])
                bad++;
        }

        priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                       greater<>>
            pq;
        for (int i = 0; i + 1 < n; i++) {
            pq.push({a[i] + a[i + 1], i});
        }

        int ops = 0;

        while (bad > 0) {
            auto [sum, i] = pq.top();
            pq.pop();

            if (!alive[i] || right[i] == n || !alive[right[i]])
                continue;
            if (a[i] + a[right[i]] != sum)
                continue;

            int j = right[i];
            int L = left[i];
            int R = right[j];

            if (isBad(L))
                bad--;
            if (isBad(i))
                bad--;
            if (isBad(j))
                bad--;

            a[i] = sum;
            alive[j] = false;
            right[i] = R;
            if (R != n)
                left[R] = i;

            if (isBad(L))
                bad++;
            if (isBad(i))
                bad++;

            if (L != -1)
                pq.push({a[L] + a[i], L});
            if (R != n)
                pq.push({a[i] + a[R], i});

            ops++;
        }
        return ops;
    }
};
