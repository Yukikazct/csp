#include<iostream>
#include<deque>
#include<algorithm>
#include<string>

using namespace std;

inline void strip_cr(string& s) 
{
    s.erase(remove(s.begin(), s.end(), '\r'), s.end());
}

int op_id = 1; 

class window
{
public:
    bool be_topped = false;
    int likeness = 0;
    long long  last_chat = 0;
    int id;
    bool talked = false;

    window(int id) : id(id), likeness(id) {}

};

deque<window> windows_queue;

void moveToFront(deque<window>::iterator it) 
{
    if (it == windows_queue.begin()) return;
    window temp = *it;
    windows_queue.erase(it);
    windows_queue.push_front(temp);
}

void Choose_u(int likeness)
{
    bool exist = false;
    for (auto it = windows_queue.begin(); it != windows_queue.end(); ++it)
    {
        if (it->likeness == likeness)
        {
            moveToFront(it);
            exist = true;
            break;
        }
    }
    if (!exist)
        cout << "OpId #" << op_id++ << ": invalid likeness." << endl;
    else
        cout << "OpId #" << op_id++ << ": success." << endl;
}

void Top_u(int likeness)
{
    // 检查是否存在
    bool exist = false;
    for (auto it = windows_queue.begin(); it != windows_queue.end(); ++it)
        if (it->likeness == likeness) { exist = true; break; }
    
    if (!exist) {
        cout << "OpId #" << op_id++ << ": invalid likeness." << endl;
        return;
    }
    
    for (auto it = windows_queue.begin(); it != windows_queue.end(); ++it)
        it->be_topped = (it->likeness == likeness);
    
    cout << "OpId #" << op_id++ << ": success." << endl;
}


void Add_u(int likeness)
{
    bool have_existed = false;
    for (auto it = windows_queue.begin(); it != windows_queue.end(); ++it)
    {
        if (it->likeness == likeness)
        {
            have_existed = true;
            break;
        }
    }
    if (!have_existed) 
    {
        windows_queue.push_back(window(likeness));
        cout << "OpId #" << op_id++ << ": success." << endl;
    } 
    else {
        cout << "OpId #" << op_id++ << ": same likeness." << endl;
    }
}

void Chat_w(int w)
{
    if (windows_queue.empty())
    {
        cout << "OpId #" << op_id++ << ": empty." << endl;
        return;
    }
    for (auto it = windows_queue.begin(); it != windows_queue.end(); ++it)
    {
        if (it->be_topped)
        {
            it->last_chat += w;
            it->talked = true;
            cout << "OpId #" << op_id++ << ": success." << endl;
            return;
        }
    }
    windows_queue.front().last_chat += w;
    windows_queue.front().talked = true; 
    
    cout << "OpId #" << op_id++ << ": success." << endl;
}

void Close_u(int likeness)
{
    bool exist = false;
    long long chat_count = 0;
    for (auto it = windows_queue.begin(); it != windows_queue.end(); ++it)
    {
        if (it->likeness == likeness)
        {
            exist = true;
            chat_count = it->last_chat;
            windows_queue.erase(it);
            break;
        }
    }
    if (exist)
        cout << "OpId #" << op_id++ << ": close " << likeness << " with " << chat_count << "." << endl;
    else
        cout << "OpId #" << op_id++ << ": invalid likeness." << endl;
}

void Untop()
{
    bool have_topped = false;
    for (auto it = windows_queue.begin(); it != windows_queue.end(); ++it)
    {
        if (it->be_topped == true)
        {
            have_topped = true;
            it->be_topped = false;
            break;
        }
    }
    if (!have_topped)
        cout << "OpId #" << op_id++ << ": no such person." << endl;
    else
        cout << "OpId #" << op_id++ << ": success." << endl;
}

void Prior_u()
{
    if (windows_queue.empty())
    {
        cout << "OpId #" << op_id++ << ": empty." << endl;
        return;
    }
    auto max_it = windows_queue.begin();
    int max_likeness = max_it->likeness;
    for (auto it = windows_queue.begin(); it != windows_queue.end(); ++it)
    {
        if (it->likeness > max_likeness)
        {
            max_likeness = it->likeness;
            max_it = it;
        }
    }
    moveToFront(max_it);
    cout << "OpId #" << op_id++ << ": success." << endl;
}

void Rotate_x(int x)
{
    if (windows_queue.empty() || x < 1 || x > windows_queue.size())
    {
        cout << "OpId #" << op_id++ << ": out of range." << endl;
        return;
    }
    auto it = windows_queue.begin();
    for (int i = 1; i < x; ++i)
        ++it;
    moveToFront(it);
    cout << "OpId #" << op_id++ << ": success." << endl;
}

void ByeBye()
{
    while (!windows_queue.empty())
    {
        auto top_it = windows_queue.begin();
        
        for (auto it = windows_queue.begin(); it != windows_queue.end(); ++it)
        {
            if (it->be_topped)
            {
                top_it = it;
                break;
            }
        }
        int u = top_it->likeness;
        long long c = top_it->last_chat;  
        if (top_it->talked) 
        { 
            cout << "OpId #" << op_id++ << ": Bye " << u << ": " << c << "." << endl;
        }
        windows_queue.erase(top_it);
    }
}




int main()
{

    int T;
    cin >> T;
    while (T--)
    {
        op_id = 1; 
        windows_queue.clear();
        int n;  
        cin >> n;
        for (int i = 0; i < n; ++i)  
        {
            string op;
            cin >> op;
            strip_cr(op);
            if (op == "Add") 
            {
                int u; 
                cin >> u; 
                Add_u(u);
            } 
            else if (op == "Close") 
            {
                int u; 
                cin >> u; 
                Close_u(u);
            } 
            else if (op == "Chat") 
            {
                int w; 
                cin >> w; 
                Chat_w(w);
            } 
            else if (op == "Rotate") 
            {
                int x; 
                cin >> x; 
                Rotate_x(x);
            } 
            else if (op == "Prior") 
            {
                Prior_u();
            } 
            else if (op == "Choose") 
            {
                int u; cin >> u; 
                Choose_u(u);
            } 
            else if (op == "Top") 
            {
                int u; 
                cin >> u; 
                Top_u(u);
            } 
            else if (op == "Untop") 
            {
                Untop();
            }
        }
         ByeBye();
    }
    return 0;
}