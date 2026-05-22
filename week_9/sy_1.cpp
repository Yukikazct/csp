#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

vector<string> lines;
int cursor_row = 1, cursor_col = 1;
bool sticky_on = false;
bool in_selection = false;
int anchor_row, anchor_col;
string clipboard;

bool pos_le(int r1, int c1, int r2, int c2)
{
    if (r1 != r2) return r1 < r2;
    return c1 <= c2;
}

void normalize_selection(int& sr, int& sc, int& er, int& ec)
{
    if (pos_le(anchor_row, anchor_col, cursor_row, cursor_col))
    {
        sr = anchor_row; sc = anchor_col;
        er = cursor_row; ec = cursor_col;
    }
    else
    {
        sr = cursor_row; sc = cursor_col;
        er = anchor_row; ec = anchor_col;
    }
}

string get_flat_text()
{
    string s;
    for (int i = 0; i < (int)lines.size(); i++)
    {
        if (i > 0) s += '\n';
        s += lines[i];
    }
    return s;
}

string get_text_in_range(int sr, int sc, int er, int ec)
{
    if (sr == er)
    {
        return lines[sr - 1].substr(sc - 1, ec - sc);
    }
    string s;
    s += lines[sr - 1].substr(sc - 1);
    s += '\n';
    for (int i = sr; i < er - 1; i++)
    {
        s += lines[i];
        s += '\n';
    }
    s += lines[er - 1].substr(0, ec - 1);
    return s;
}

void delete_range(int sr, int sc, int er, int ec)
{
    if (sr == er)
    {
        lines[sr - 1].erase(sc - 1, ec - sc);
        return;
    }
    lines[sr - 1] = lines[sr - 1].substr(0, sc - 1) + lines[er - 1].substr(ec - 1);
    lines.erase(lines.begin() + sr, lines.begin() + er);
}

void delete_selection()
{
    int sr, sc, er, ec;
    normalize_selection(sr, sc, er, ec);
    delete_range(sr, sc, er, ec);
    cursor_row = sr;
    cursor_col = sc;
    in_selection = false;
}

void insert_flat_text(const string& text)
{
    vector<string> parts;
    size_t pos = 0;
    while (pos <= text.size())
    {
        size_t nl = text.find('\n', pos);
        if (nl == string::npos)
        {
            parts.push_back(text.substr(pos));
            break;
        }
        parts.push_back(text.substr(pos, nl - pos));
        pos = nl + 1;
        if (pos > text.size())
        {
            parts.push_back("");
        }
    }
    if (parts.empty()) parts.push_back("");

    int r = cursor_row - 1;
    int c = cursor_col - 1;
    string left = lines[r].substr(0, c);
    string right = lines[r].substr(c);

    if (parts.size() == 1)
    {
        lines[r] = left + parts[0] + right;
        cursor_col += (int)parts[0].size();
    }
    else
    {
        lines[r] = left + parts[0];
        for (int i = 1; i < (int)parts.size() - 1; i++)
        {
            lines.insert(lines.begin() + r + i, parts[i]);
        }
        int last_idx = r + (int)parts.size() - 1;
        lines.insert(lines.begin() + last_idx, parts.back() + right);
        char last_char = text.back();
        if (last_char == '\n')
        {
            cursor_row = last_idx + 1;
            cursor_col = 1;
        }
        else
        {
            cursor_row = last_idx + 1;
            cursor_col = (int)parts.back().size() + 1;
        }
    }
}

int count_visible(const string& s)
{
    int cnt = 0;
    for (char ch : s)
    {
        if (ch != ' ' && ch != '\n') cnt++;
    }
    return cnt;
}

int count_occurrences(const string& text, const string& word)
{
    if (word.empty()) return 0;
    int cnt = 0;
    size_t pos = 0;
    while ((pos = text.find(word, pos)) != string::npos)
    {
        cnt++;
        pos++;
    }
    return cnt;
}

int main()
{
    lines.push_back("");

    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        string line;
        getline(cin, line);
        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (sticky_on && cmd != "MOVE" && cmd != "SHIFT")
        {
            continue;
        }

        if (cmd == "MOVE")
        {
            string sub;
            iss >> sub;
            if (in_selection)
            {
                in_selection = false;
            }
            if (sub == "Home")
            {
                cursor_col = 1;
            }
            else if (sub == "End")
            {
                cursor_col = (int)lines[cursor_row - 1].size() + 1;
            }
            else if (sub == "Up")
            {
                if (cursor_row > 1)
                {
                    cursor_row--;
                    int len = (int)lines[cursor_row - 1].size();
                    if (cursor_col > len + 1) cursor_col = len + 1;
                }
            }
            else if (sub == "Down")
            {
                if (cursor_row < (int)lines.size())
                {
                    cursor_row++;
                    int len = (int)lines[cursor_row - 1].size();
                    if (cursor_col > len + 1) cursor_col = len + 1;
                }
            }
            else if (sub == "Left")
            {
                if (cursor_col > 1)
                {
                    cursor_col--;
                }
                else if (cursor_row > 1)
                {
                    cursor_row--;
                    cursor_col = (int)lines[cursor_row - 1].size() + 1;
                }
            }
            else if (sub == "Right")
            {
                int len = (int)lines[cursor_row - 1].size();
                if (cursor_col <= len)
                {
                    cursor_col++;
                }
                else if (cursor_row < (int)lines.size())
                {
                    cursor_row++;
                    cursor_col = 1;
                }
            }
        }
        else if (cmd == "INSERT")
        {
            string sub;
            iss >> sub;
            if (sub == "Paste" && clipboard.empty())
            {
                // do nothing
            }
            else if (in_selection)
            {
                delete_selection();
            }
            if (sub == "Char")
            {
                char ch;
                iss >> ch;
                string s(1, ch);
                insert_flat_text(s);
            }
            else if (sub == "Enter")
            {
                int r = cursor_row - 1;
                int c = cursor_col - 1;
                string left = lines[r].substr(0, c);
                string right = lines[r].substr(c);
                lines[r] = left;
                lines.insert(lines.begin() + r + 1, right);
                cursor_row = r + 2;
                cursor_col = 1;
            }
            else if (sub == "Space")
            {
                insert_flat_text(" ");
            }
            else if (sub == "Paste")
            {
                if (!clipboard.empty())
                {
                    insert_flat_text(clipboard);
                }
            }
        }
        else if (cmd == "REMOVE")
        {
            string sub;
            iss >> sub;
            if (in_selection)
            {
                delete_selection();
                continue;
            }
            if (sub == "Del")
            {
                int len = (int)lines[cursor_row - 1].size();
                if (cursor_col <= len)
                {
                    lines[cursor_row - 1].erase(cursor_col - 1, 1);
                }
                else if (cursor_row < (int)lines.size())
                {
                    lines[cursor_row - 1] += lines[cursor_row];
                    lines.erase(lines.begin() + cursor_row);
                }
            }
            else if (sub == "Backspace")
            {
                if (cursor_col > 1)
                {
                    cursor_col--;
                    lines[cursor_row - 1].erase(cursor_col - 1, 1);
                }
                else if (cursor_row > 1)
                {
                    int prev_len = (int)lines[cursor_row - 2].size();
                    lines[cursor_row - 2] += lines[cursor_row - 1];
                    lines.erase(lines.begin() + cursor_row - 1);
                    cursor_row--;
                    cursor_col = prev_len + 1;
                }
            }
        }
        else if (cmd == "SHIFT")
        {
            sticky_on = !sticky_on;
            if (sticky_on)
            {
                if (in_selection)
                {
                    in_selection = false;
                    // 保留上一次的记录点（anchor不变）
                }
                else
                {
                    anchor_row = cursor_row;
                    anchor_col = cursor_col;
                }
            }
            else
            {
                if (!(anchor_row == cursor_row && anchor_col == cursor_col))
                {
                    in_selection = true;
                }
            }
        }
        else if (cmd == "FIND")
        {
            string word;
            iss >> word;
            if (in_selection)
            {
                int sr, sc, er, ec;
                normalize_selection(sr, sc, er, ec);
                string sel = get_text_in_range(sr, sc, er, ec);
                cout << count_occurrences(sel, word) << "\n";
            }
            else
            {
                string flat = get_flat_text();
                cout << count_occurrences(flat, word) << "\n";
            }
        }
        else if (cmd == "COUNT")
        {
            if (in_selection)
            {
                int sr, sc, er, ec;
                normalize_selection(sr, sc, er, ec);
                string sel = get_text_in_range(sr, sc, er, ec);
                cout << count_visible(sel) << "\n";
            }
            else
            {
                string flat = get_flat_text();
                cout << count_visible(flat) << "\n";
            }
        }
        else if (cmd == "COPY")
        {
            if (in_selection)
            {
                int sr, sc, er, ec;
                normalize_selection(sr, sc, er, ec);
                clipboard = get_text_in_range(sr, sc, er, ec);
            }
            else
            {
                string& cur_line = lines[cursor_row - 1];
                if (!cur_line.empty())
                {
                    clipboard = cur_line;
                }
            }
        }
        else if (cmd == "PRINT")
        {
            for (int j = 0; j < (int)lines.size(); j++)
            {
                cout << lines[j];
                if (j < (int)lines.size() - 1) cout << '\n';
            }
            cout << '\n';
        }
    }

    return 0;
}
