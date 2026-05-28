const int MAX_NODES = 500005;

int nxt[MAX_NODES][26];
int best_len[MAX_NODES];
int best_idx[MAX_NODES];

class Solution {
public:

    void relax(int node, int len, int idx) {

        if (len < best_len[node]) {
            best_len[node] = len;
            best_idx[node] = idx;
        }
        else if (len == best_len[node] && idx < best_idx[node]) {
            best_idx[node] = idx;
        }
    }

    vector<int> stringIndices(vector<string>& wordsContainer,
                              vector<string>& wordsQuery) {

        int nodeCnt = 1;

        memset(nxt[0], -1, sizeof(nxt[0]));
        best_len[0] = 1e9;
        best_idx[0] = 1e9;

        for (int i = 0; i < wordsContainer.size(); i++) {

            int curr = 0;
            int len = wordsContainer[i].size();

            relax(curr, len, i);

            for (int j = len - 1; j >= 0; j--) {

                int c = wordsContainer[i][j] - 'a';

                if (nxt[curr][c] == -1) {

                    nxt[curr][c] = nodeCnt;

                    memset(nxt[nodeCnt], -1, sizeof(nxt[nodeCnt]));
                    best_len[nodeCnt] = 1e9;
                    best_idx[nodeCnt] = 1e9;

                    nodeCnt++;
                }

                curr = nxt[curr][c];

                relax(curr, len, i);
            }
        }

        vector<int> ans;
        ans.reserve(wordsQuery.size());

        for (auto &q : wordsQuery) {

            int curr = 0;

            for (int j = q.size() - 1; j >= 0; j--) {

                int c = q[j] - 'a';

                if (nxt[curr][c] == -1)
                    break;

                curr = nxt[curr][c];
            }

            ans.push_back(best_idx[curr]);
        }

        return ans;
    }
};