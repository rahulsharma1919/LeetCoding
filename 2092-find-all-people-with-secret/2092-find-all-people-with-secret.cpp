class Solution {
public:
    vector<int> parent, rankv;

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return;
        if (rankv[a] < rankv[b])
            swap(a, b);
        parent[b] = a;
        if (rankv[a] == rankv[b])
            rankv[a]++;
    }

    vector<int> findAllPeople(int n, vector<vector<int>>& meetings,
                              int firstPerson) {
        parent.resize(n);
        rankv.assign(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;

        unite(0, firstPerson);

        sort(meetings.begin(), meetings.end(),
             [](auto& a, auto& b) { return a[2] < b[2]; });

        int i = 0;
        while (i < meetings.size()) {
            int time = meetings[i][2];
            vector<int> persons;

            int j = i;
            while (j < meetings.size() && meetings[j][2] == time) {
                unite(meetings[j][0], meetings[j][1]);
                persons.push_back(meetings[j][0]);
                persons.push_back(meetings[j][1]);
                j++;
            }

            for (int p : persons) {
                if (find(p) != find(0)) {
                    parent[p] = p;
                }
            }

            i = j;
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (find(i) == find(0))
                ans.push_back(i);
        }
        return ans;
    }
};
