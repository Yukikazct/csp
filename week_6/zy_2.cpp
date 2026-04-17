#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

using ll = long long;

struct Node {
    string name;
    bool is_dir;
    ll file_size;
    ll ld;
    ll lr;
    ll direct_sum;
    ll subtree_sum;
    Node* parent;
    unordered_map<string, Node*> children;

    Node(const string& node_name, bool dir, Node* fa = nullptr)
        : name(node_name),
          is_dir(dir),
          file_size(0),
          ld(0),
          lr(0),
          direct_sum(0),
          subtree_sum(0),
          parent(fa) {}
};

Node* root = new Node("/", true);

vector<string> split_path(const string& path) {
    vector<string> parts;
    string current;
    for (char ch : path) {
        if (ch == '/') {
            if (!current.empty()) {
                parts.push_back(current);
                current.clear();
            }
        } else {
            current.push_back(ch);
        }
    }
    if (!current.empty()) {
        parts.push_back(current);
    }
    return parts;
}

Node* find_node(const vector<string>& parts) {
    Node* cur = root;
    for (const string& part : parts) {
        auto it = cur->children.find(part);
        if (it == cur->children.end() || !cur->is_dir) {
            return nullptr;
        }
        cur = it->second;
    }
    return cur;
}

void delete_subtree(Node* node) {
    if (node->is_dir) {
        for (auto& [_, child] : node->children) {
            delete_subtree(child);
        }
    }
    delete node;
}

void rollback_created_dirs(vector<Node*>& created_dirs) {
    for (int i = static_cast<int>(created_dirs.size()) - 1; i >= 0; --i) {
        Node* dir = created_dirs[i];
        dir->parent->children.erase(dir->name);
        delete dir;
    }
}

void apply_file_delta(Node* parent, ll delta) {
    if (parent == nullptr || delta == 0) {
        return;
    }
    parent->direct_sum += delta;
    for (Node* cur = parent; cur != nullptr; cur = cur->parent) {
        cur->subtree_sum += delta;
    }
}

bool can_create_or_update(Node* parent, ll delta) {
    if (parent->ld != 0 && parent->direct_sum + delta > parent->ld) {
        return false;
    }
    for (Node* cur = parent; cur != nullptr; cur = cur->parent) {
        if (cur->lr != 0 && cur->subtree_sum + delta > cur->lr) {
            return false;
        }
    }
    return true;
}

void create_file(const string& path, ll size) {
    vector<string> parts = split_path(path);
    string file_name = parts.back();
    parts.pop_back();

    Node* parent = root;
    vector<Node*> created_dirs;

    for (const string& dir_name : parts) {
        auto it = parent->children.find(dir_name);
        if (it == parent->children.end()) {
            Node* new_dir = new Node(dir_name, true, parent);
            parent->children[dir_name] = new_dir;
            created_dirs.push_back(new_dir);
            parent = new_dir;
            continue;
        }
        if (!it->second->is_dir) {
            rollback_created_dirs(created_dirs);
            cout << "N\n";
            return;
        }
        parent = it->second;
    }

    Node* target = nullptr;
    ll old_size = 0;
    auto it = parent->children.find(file_name);
    if (it != parent->children.end()) {
        target = it->second;
        if (target->is_dir) {
            rollback_created_dirs(created_dirs);
            cout << "N\n";
            return;
        }
        old_size = target->file_size;
    }

    ll delta = size - old_size;
    if (!can_create_or_update(parent, delta)) {
        rollback_created_dirs(created_dirs);
        cout << "N\n";
        return;
    }

    if (target == nullptr) {
        target = new Node(file_name, false, parent);
        parent->children[file_name] = target;
    }
    target->file_size = size;
    apply_file_delta(parent, delta);

    cout << "Y\n";
}

void remove_path(const string& path) {
    vector<string> parts = split_path(path);
    Node* target = find_node(parts);
    if (target == nullptr) {
        cout << "Y\n";
        return;
    }

    Node* parent = target->parent;
    ll removed_sum = target->is_dir ? target->subtree_sum : target->file_size;
    ll removed_direct = target->is_dir ? 0 : target->file_size;

    if (parent != nullptr) {
        parent->direct_sum -= removed_direct;
        for (Node* cur = parent; cur != nullptr; cur = cur->parent) {
            cur->subtree_sum -= removed_sum;
        }
        parent->children.erase(target->name);
        delete_subtree(target);
    }

    cout << "Y\n";
}

void set_quota(const string& path, ll ld, ll lr) {
    vector<string> parts = split_path(path);
    Node* dir = find_node(parts);
    if (dir == nullptr || !dir->is_dir) {
        cout << "N\n";
        return;
    }
    if (ld != 0 && dir->direct_sum > ld) {
        cout << "N\n";
        return;
    }
    if (lr != 0 && dir->subtree_sum > lr) {
        cout << "N\n";
        return;
    }

    dir->ld = ld;
    dir->lr = lr;
    cout << "Y\n";
}

int main() {

    int n;
    cin >> n;
    while (n--) {
        char op;
        cin >> op;
        if (op == 'C') {
            string path;
            ll size;
            cin >> path >> size;
            create_file(path, size);
        } else if (op == 'R') {
            string path;
            cin >> path;
            remove_path(path);
        } else if (op == 'Q') {
            string path;
            ll ld, lr;
            cin >> path >> ld >> lr;
            set_quota(path, ld, lr);
        }
    }

    return 0;
}
