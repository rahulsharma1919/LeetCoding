class Solution {
public:
    int e2[10], e3[10], e5[10], e7[10];
    long long A, B, C, D;
    vector<vector<int>> dp2_3;

    void initExponents() {
        int E2[10] = {0, 0, 1, 0, 2, 0, 1, 0, 3, 0};
        int E3[10] = {0, 0, 0, 1, 0, 0, 1, 0, 0, 2};
        int E5[10] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
        int E7[10] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
        for (int i = 0; i < 10; i++) {
            e2[i] = E2[i];
            e3[i] = E3[i];
            e5[i] = E5[i];
            e7[i] = E7[i];
        }
    }

    void buildDp() {
        dp2_3.assign(A + 1, vector<int>(B + 1, INT_MAX / 2));
        dp2_3[0][0] = 0;
        int digs[6] = {2, 3, 4, 6, 8, 9};
        for (int x = 0; x <= A; x++) {
            for (int y = 0; y <= B; y++) {
                if (x == 0 && y == 0)
                    continue;
                int best = INT_MAX / 2;
                for (int d : digs) {
                    int nx = max(0, x - e2[d]);
                    int ny = max(0, y - e3[d]);
                    best = min(best, dp2_3[nx][ny] + 1);
                }
                dp2_3[x][y] = best;
            }
        }
    }

    long long minDigits(long long a, long long b, long long c, long long d) {
        a = min(max(0LL, a), A);
        b = min(max(0LL, b), B);
        c = min(max(0LL, c), C);
        d = min(max(0LL, d), D);
        return c + d + dp2_3[(int)a][(int)b];
    }

    string buildSuffix(long long a, long long b, long long c, long long d,
                       long long m) {
        string res;
        for (long long pos = 0; pos < m; pos++) {
            long long remAfter = m - pos - 1;
            for (int v = 1; v <= 9; v++) {
                long long na = max(0LL, a - e2[v]);
                long long nb = max(0LL, b - e3[v]);
                long long nc = max(0LL, c - e5[v]);
                long long nd = max(0LL, d - e7[v]);
                if (minDigits(na, nb, nc, nd) <= remAfter) {
                    res.push_back('0' + v);
                    a = na;
                    b = nb;
                    c = nc;
                    d = nd;
                    break;
                }
            }
        }
        return res;
    }

    string smallestNumber(string num, long long t) {
        initExponents();
        A = B = C = D = 0;
        long long tt = t;
        while (tt % 2 == 0) {
            tt /= 2;
            A++;
        }
        while (tt % 3 == 0) {
            tt /= 3;
            B++;
        }
        while (tt % 5 == 0) {
            tt /= 5;
            C++;
        }
        while (tt % 7 == 0) {
            tt /= 7;
            D++;
        }
        if (tt != 1)
            return "-1";

        buildDp();

        int n = num.size();
        vector<long long> cumA(n + 1, 0), cumB(n + 1, 0), cumC(n + 1, 0),
            cumD(n + 1, 0);
        int firstZero = n;
        for (int i = 0; i < n; i++) {
            int dgt = num[i] - '0';
            if (dgt == 0 && firstZero == n)
                firstZero = i;
            cumA[i + 1] = min(A, cumA[i] + e2[dgt]);
            cumB[i + 1] = min(B, cumB[i] + e3[dgt]);
            cumC[i + 1] = min(C, cumC[i] + e5[dgt]);
            cumD[i + 1] = min(D, cumD[i] + e7[dgt]);
        }

        if (firstZero == n && cumA[n] >= A && cumB[n] >= B && cumC[n] >= C &&
            cumD[n] >= D)
            return num;

        int startPos = min(firstZero, n - 1);
        for (int pos = startPos; pos >= 0; pos--) {
            long long ra = A - cumA[pos], rb = B - cumB[pos];
            long long rc = C - cumC[pos], rd = D - cumD[pos];
            int startDigit = (num[pos] - '0') + 1;
            for (int v = startDigit; v <= 9; v++) {
                long long na = max(0LL, ra - e2[v]);
                long long nb = max(0LL, rb - e3[v]);
                long long nc = max(0LL, rc - e5[v]);
                long long nd = max(0LL, rd - e7[v]);
                long long m = n - pos - 1;
                if (minDigits(na, nb, nc, nd) <= m)
                    return num.substr(0, pos) + char('0' + v) +
                           buildSuffix(na, nb, nc, nd, m);
            }
        }

        long long L = max((long long)n + 1, minDigits(A, B, C, D));
        return buildSuffix(A, B, C, D, L);
    }
};