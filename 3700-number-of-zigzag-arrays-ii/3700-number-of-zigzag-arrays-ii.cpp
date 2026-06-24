class Solution {
public:
    const int MOD = 1e9 + 7;
    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix& A, const Matrix& B) {
        int sz = A.size();
        Matrix C(sz, vector<long long>(sz, 0));
        for (int i = 0; i < sz; i++)
            for (int k = 0; k < sz; k++) {
                if (!A[i][k])
                    continue;
                for (int j = 0; j < sz; j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        return C;
    }

    Matrix matpow(Matrix M, long long p) {
        int sz = M.size();
        Matrix result(sz, vector<long long>(sz, 0));
        for (int i = 0; i < sz; i++)
            result[i][i] = 1;
        while (p > 0) {
            if (p & 1)
                result = multiply(result, M);
            M = multiply(M, M);
            p >>= 1;
        }
        return result;
    }

    int zigZagArrays(int n, int l, int r) {
        int sz = r - l + 1;
        int dim = 2 * sz;

        if (n == 1)
            return sz;

        vector<long long> state(dim);
        for (int v = 0; v < sz; v++) {
            state[v] = v;
            state[sz + v] = sz - 1 - v;
        }

        if (n == 2) {
            long long ans = 0;
            for (auto x : state)
                ans = (ans + x) % MOD;
            return ans;
        }

        Matrix T(dim, vector<long long>(dim, 0));
        for (int v = 0; v < sz; v++) {
            for (int w = 0; w < v; w++)
                T[v][sz + w] = 1;
            for (int w = v + 1; w < sz; w++)
                T[sz + v][w] = 1;
        }

        Matrix Tn = matpow(T, n - 2);

        vector<long long> res(dim, 0);
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                res[i] = (res[i] + Tn[i][j] * state[j]) % MOD;

        long long ans = 0;
        for (auto x : res)
            ans = (ans + x) % MOD;
        return (int)ans;
    }
};