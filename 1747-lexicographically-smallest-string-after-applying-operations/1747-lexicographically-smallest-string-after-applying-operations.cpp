class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        unordered_set<string> visited;
        queue<string> q;
        string smallest = s;

        q.push(s);
        visited.insert(s);

        while (!q.empty()) {
            string curr = q.front();
            q.pop();

            if (curr < smallest)
                smallest = curr;

            string added = curr;
            for (int i = 1; i < curr.size(); i += 2) {
                added[i] = (added[i] - '0' + a) % 10 + '0';
            }

            if (!visited.count(added)) {
                visited.insert(added);
                q.push(added);
            }

            string rotated =
                curr.substr(curr.size() - b) + curr.substr(0, curr.size() - b);
            if (!visited.count(rotated)) {
                visited.insert(rotated);
                q.push(rotated);
            }
        }

        return smallest;
    }
};
