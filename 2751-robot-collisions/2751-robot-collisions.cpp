class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions,
                                      vector<int>& healths, string directions) {
        int n = positions.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(),
             [&](int a, int b) { return positions[a] < positions[b]; });

        stack<int> st;
        vector<bool> dead(n, false);

        for (int i : idx) {
            if (directions[i] == 'R') {
                st.push(i);
            } else {
                while (!st.empty()) {
                    int top = st.top();
                    if (healths[top] > healths[i]) {
                        healths[top]--;
                        dead[i] = true;
                        break;
                    } else if (healths[top] < healths[i]) {
                        dead[top] = true;
                        healths[i]--;
                        st.pop();
                    } else {
                        dead[top] = dead[i] = true;
                        st.pop();
                        break;
                    }
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++)
            if (!dead[i])
                ans.push_back(healths[i]);
        return ans;
    }
};