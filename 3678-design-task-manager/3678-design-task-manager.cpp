class TaskManager {
    struct Task {
        int priority, taskId, userId;
    };
    
    struct Compare {
        bool operator()(const Task& a, const Task& b) const {
            if (a.priority == b.priority) return a.taskId < b.taskId;
            return a.priority < b.priority;
        }
    };
    
    unordered_map<int, pair<int,int>> taskInfo; // taskId -> {userId, priority}
    priority_queue<Task, vector<Task>, Compare> pq;

public:
    TaskManager(vector<vector<int>>& tasks) {
        for (auto &t : tasks) {
            int userId = t[0], taskId = t[1], priority = t[2];
            taskInfo[taskId] = {userId, priority};
            pq.push({priority, taskId, userId});
        }
    }
    
    void add(int userId, int taskId, int priority) {
        taskInfo[taskId] = {userId, priority};
        pq.push({priority, taskId, userId});
    }
    
    void edit(int taskId, int newPriority) {
        auto [userId, _] = taskInfo[taskId];
        taskInfo[taskId] = {userId, newPriority};
        pq.push({newPriority, taskId, userId});
    }
    
    void rmv(int taskId) {
        // Mark as removed by erasing — stale heap entries will be skipped
        taskInfo.erase(taskId);
    }
    
    int execTop() {
        while (!pq.empty()) {
            auto top = pq.top(); pq.pop();
            if (taskInfo.count(top.taskId) && taskInfo[top.taskId].second == top.priority) {
                int userId = taskInfo[top.taskId].first;
                taskInfo.erase(top.taskId); // remove after execution
                return userId;
            }
        }
        return -1;
    }
};
