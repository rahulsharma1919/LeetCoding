class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        int N = n + 1;

        // Build suffix array using counting sort
        vector<int> s(N);
        for (int i = 0; i < n; i++)
            s[i] = nums[i];

        s[n] = 0; // Sentinel

        vector<int> p(N), c(N);
        vector<int> cnt(max(100001, N), 0);

        for (int x : s)
            cnt[x]++;

        for (int i = 1; i < cnt.size(); i++)
            cnt[i] += cnt[i - 1];

        for (int i = N - 1; i >= 0; i--)
            p[--cnt[s[i]]] = i;

        c[p[0]] = 0;
        int classes = 1;

        for (int i = 1; i < N; i++) {
            if (s[p[i]] != s[p[i - 1]])
                classes++;
            c[p[i]] = classes - 1;
        }

        for (int k = 0; (1 << k) < N; k++) {
            int len = 1 << k;
            vector<int> pn(N);

            for (int i = 0; i < N; i++) {
                pn[i] = p[i] - len;
                if (pn[i] < 0)
                    pn[i] += N;
            }

            fill(cnt.begin(), cnt.begin() + classes, 0);

            for (int x : pn)
                cnt[c[x]]++;

            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i - 1];

            for (int i = N - 1; i >= 0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];

            vector<int> cn(N);
            cn[p[0]] = 0;
            int newClasses = 1;

            for (int i = 1; i < N; i++) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + len) % N]};

                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + len) % N]};

                if (cur != prev)
                    newClasses++;

                cn[p[i]] = newClasses - 1;
            }

            c.swap(cn);
            classes = newClasses;
        }

        // Remove the sentinel suffix
        vector<int> sa(p.begin() + 1, p.end());

        // Build LCP array using Kasai's algorithm
        vector<int> rank(n), lcp(n, 0);

        for (int i = 0; i < n; i++)
            rank[sa[i]] = i;

        int h = 0;

        for (int i = 0; i < n; i++) {
            int r = rank[i];

            if (r == 0)
                continue;

            int j = sa[r - 1];

            while (i + h < n && j + h < n && nums[i + h] == nums[j + h]) {
                h++;
            }

            lcp[r] = h;

            if (h > 0)
                h--;
        }

        // Find the shortest unique subarray
        int ans = n;

        for (int i = 0; i < n; i++) {
            int r = rank[i];

            int common = 0;

            if (r > 0)
                common = max(common, lcp[r]);

            if (r + 1 < n)
                common = max(common, lcp[r + 1]);

            int need = common + 1;

            if (need <= n - i)
                ans = min(ans, need);
        }

        return ans;
    }
};