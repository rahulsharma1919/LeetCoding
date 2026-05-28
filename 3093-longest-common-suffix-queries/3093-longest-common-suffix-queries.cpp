class Solution {
public:
    struct Node {
        int child[26];
        int bestIdx;

        Node() {
            memset(child, -1, sizeof(child));
            bestIdx = -1;
        }
    };

    vector<Node> trie;

    bool better(int a, int b, vector<string>& wordsContainer) {

        if (b == -1)
            return true;

        if (wordsContainer[a].size() != wordsContainer[b].size())
            return wordsContainer[a].size() < wordsContainer[b].size();

        return a < b;
    }

    void insert(string& word, int idx, vector<string>& wordsContainer) {

        int node = 0;

        if (better(idx, trie[node].bestIdx, wordsContainer))
            trie[node].bestIdx = idx;

        for (int i = word.size() - 1; i >= 0; --i) {

            int c = word[i] - 'a';

            if (trie[node].child[c] == -1) {
                trie[node].child[c] = trie.size();
                trie.push_back(Node());
            }

            node = trie[node].child[c];

            if (better(idx, trie[node].bestIdx, wordsContainer))
                trie[node].bestIdx = idx;
        }
    }

    int query(string& word) {

        int node = 0;

        for (int i = word.size() - 1; i >= 0; --i) {

            int c = word[i] - 'a';

            if (trie[node].child[c] == -1)
                break;

            node = trie[node].child[c];
        }

        return trie[node].bestIdx;
    }

    vector<int> stringIndices(vector<string>& wordsContainer,
                              vector<string>& wordsQuery) {

        trie.reserve(500000 + 5);
        trie.push_back(Node());

        for (int i = 0; i < wordsContainer.size(); ++i) {
            insert(wordsContainer[i], i, wordsContainer);
        }

        vector<int> ans;

        for (auto& q : wordsQuery) {
            ans.push_back(query(q));
        }

        return ans;
    }
};