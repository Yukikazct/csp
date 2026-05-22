#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

typedef long long ll;

static unsigned int p = 1;

int myrand() {
    p = p * 1103515245 + 12345;
    return ((unsigned int)(p / 65536) % 100);
}

struct Task {
    int id;
    string name;
    int duration;
    int pending_seq;
};

struct SFCompare {
    bool operator()(const Task& a, const Task& b) const {
        if (a.duration != b.duration) return a.duration > b.duration;
        return a.name < b.name;
    }
};

struct LFCompare {
    bool operator()(const Task& a, const Task& b) const {
        if (a.duration != b.duration) return a.duration < b.duration;
        return a.name < b.name;
    }
};

struct CompletionEvent {
    ll time;
    int ws_idx;
    bool operator>(const CompletionEvent& o) const {
        return time > o.time;
    }
};

struct Workshop {
    string strategy;
    ll busy_until;
    Task current_task;
    queue<Task> tf_queue;
    priority_queue<Task, vector<Task>, SFCompare> sf_pq;
    priority_queue<Task, vector<Task>, LFCompare> lf_pq;
    int pending_seq;

    Workshop() : busy_until(0), pending_seq(0) {}

    void addPending(const Task& t) {
        if (strategy == "TF") {
            Task tt = t;
            tt.pending_seq = pending_seq++;
            tf_queue.push(tt);
        } else if (strategy == "SF") {
            sf_pq.push(t);
        } else {
            lf_pq.push(t);
        }
    }

    bool hasPending() const {
        if (strategy == "TF") return !tf_queue.empty();
        if (strategy == "SF") return !sf_pq.empty();
        return !lf_pq.empty();
    }

    Task popPending() {
        Task t;
        if (strategy == "TF") {
            t = tf_queue.front();
            tf_queue.pop();
        } else if (strategy == "SF") {
            t = sf_pq.top();
            sf_pq.pop();
        } else {
            t = lf_pq.top();
            lf_pq.pop();
        }
        return t;
    }
};

struct Result {
    ll time;
    int id;
    string name;
    bool operator<(const Result& o) const {
        if (time != o.time) return time < o.time;
        return id < o.id;
    }
};

int main() {

    int n, m;
    cin >> n >> m;

    unordered_map<string, int> ws_map;
    vector<Workshop> workshops(n);

    for (int i = 0; i < n; i++) {
        string name, strategy;
        cin >> name >> strategy;
        ws_map[name] = i;
        workshops[i].strategy = strategy;
    }

    vector<Result> results;
    results.reserve(m);
    priority_queue<CompletionEvent, vector<CompletionEvent>, greater<CompletionEvent>> heap;

    for (int op = 0; op < m; op++) {
        ll t;
        string s;
        int d, k;
        cin >> t >> s >> d >> k;
        vector<string> candidates(k);
        for (int i = 0; i < k; i++) cin >> candidates[i];

        while (!heap.empty() && heap.top().time <= t) {
            auto ev = heap.top();
            heap.pop();
            ll comp_time = ev.time;
            int ws_idx = ev.ws_idx;

            Workshop& ws = workshops[ws_idx];
            results.push_back({comp_time, ws.current_task.id, ws.current_task.name});

            if (ws.hasPending()) {
                Task next = ws.popPending();
                ws.current_task = next;
                ws.busy_until = comp_time + next.duration;
                heap.push({ws.busy_until, ws_idx});
            } else {
                ws.busy_until = 0;
            }
        }

        int prob = 100 / k;
        int assigned = -1;
        for (int i = 0; i < k - 1; i++) {
            if (prob > myrand()) {
                assigned = ws_map[candidates[i]];
                break;
            }
        }
        if (assigned == -1) assigned = ws_map[candidates[k - 1]];

        Task nt;
        nt.id = op;
        nt.name = s;
        nt.duration = d;

        Workshop& ws = workshops[assigned];
        if (ws.busy_until == 0) {
            ws.current_task = nt;
            ws.busy_until = t + d;
            heap.push({ws.busy_until, assigned});
        } else {
            ws.addPending(nt);
        }
    }

    while (!heap.empty()) {
        auto ev = heap.top();
        heap.pop();
        ll comp_time = ev.time;
        int ws_idx = ev.ws_idx;

        Workshop& ws = workshops[ws_idx];
        results.push_back({comp_time, ws.current_task.id, ws.current_task.name});

        if (ws.hasPending()) {
            Task next = ws.popPending();
            ws.current_task = next;
            ws.busy_until = comp_time + next.duration;
            heap.push({ws.busy_until, ws_idx});
        }
    }

    sort(results.begin(), results.end());

    for (const auto& r : results) {
        cout << r.time << " " << r.name << "\n";
    }

    return 0;
}
