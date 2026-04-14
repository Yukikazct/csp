#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

typedef long long ll;
typedef unordered_map<string, ll> Map;

vector<string> split(const string &str, char delimiter) 
{
    vector<string> res;
    string temp;
    for (int i = 0 ; i < str.size() ; i++) 
    {
        char c = str[i];
        if (c == delimiter) 
        {
            if (!temp.empty()) 
            {
                res.push_back(temp);
                temp.clear();
            }
        } 
        else 
        {
            temp += c;
        }
    }
    if (!temp.empty()) res.push_back(temp);
    return res;
}//分割表达式


ll parseNumber(const string &s, int &pos) 
{
    ll num = 0;
    int n = s.size();
    while (pos < n && isdigit(s[pos])) 
    {
        num = num * 10 + (s[pos] - '0');
        pos++;
    }
    if(num == 0 ) return 1;
    else return num;
}//从字符将连续的数字转化为long long


Map parseFormula(const string &s, int &pos) 
{
    Map current;
    int n = s.size();
    while (pos < n) 
    {
        if (s[pos] == ')') 
        {
            pos++;
            return current;//结束这一层括号
        }
        else if (s[pos] == '(') 
        {
            pos++;
            Map sub = parseFormula(s, pos);
            ll mul = parseNumber(s, pos);
            for (auto &[k, v] : sub)
            {
                current[k] += v * mul;
            }//乘下标数字
        }
        else if (isupper(s[pos])) 
        {
            string elem;
            elem += s[pos];
            pos++;
            if (pos < n && islower(s[pos])) 
            {
                elem += s[pos];
                pos++;
            }
            ll cnt = parseNumber(s, pos);
            current[elem] += cnt;
        } 
        else 
        {
            pos++;
        }
    }
    return current;
}

Map parse_expr(const string &expr) {
    Map total;
    vector<string> terms = split(expr, '+');
    for (string &term : terms) 
    {
        int pos = 0;
        ll coeff = parseNumber(term, pos);
        Map formula = parseFormula(term, pos);
        for (auto &[k, v] : formula)
        {
            total[k] += v * coeff;
        } 
    }
    return total;
}

bool is_balanced(const string &eq) 
{
    vector<string> parts = split(eq, '=');
    Map left = parse_expr(parts[0]);
    Map right = parse_expr(parts[1]);
    return left == right;
}

int main() 
{
    
    int n;
    cin >> n;
    
    while (n--) 
    {
        string eq;
        cin>>eq;
        cout << (is_balanced(eq) ? "Y" : "N") << endl;
    }
    return 0;
}