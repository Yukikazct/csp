#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cctype>
#include <algorithm>

using namespace std;

using Poly = vector<long long>;//记录多项式不同次数的系数

struct StackFrame 
{
    string type;
    Poly poly;
};

Poly poly_Mul(const Poly& a, const Poly& b) 
{
    Poly res(11, 0);
    for (int i = 0; i < a.size() && i <= 10; i++) 
    {
        if (a[i] == 0) continue;
        for (int j = 0; j < b.size() && i + j <= 10; j++) 
        {
            if (b[j] == 0) continue;
            res[i + j] += a[i] * b[j];
        }
    }
    return res;
}

Poly poly_Add(const Poly& a, const Poly& b) 
{
    Poly res(11, 0);
    for (int i = 0; i <= 10; i++) 
    {
        res[i] = a[i] + b[i];
    }
    return res;
}

Poly polyMul_Const(const Poly& a, long long c) 
{
    Poly res(11, 0);
    for (int i = 0; i <= 10; i++) 
    {
        res[i] = a[i] * c;
    }
    return res;
}

Poly constPoly(long long c) 
{
    Poly res(11, 0);
    res[0] = c;
    return res;
}

Poly nPoly() 
{
    Poly res(11, 0);
    res[1] = 1;
    return res;
}

enum Type { BEGIN, LOOP, END, OP, NUMBER, N};

bool isNumber(const string& s) 
{
    for(char c : s)
    {
        if(!isdigit(c)) return false;
    }
        
    return !s.empty();
    
}

Type get_Type(const string& word) 
{
    if (word == "BEGIN") return BEGIN;
    if (word == "LOOP")  return LOOP;
    if (word == "END")   return END;
    if (word == "OP")    return OP;
    if (word == "n")     return N;
    if (isNumber(word))  return NUMBER;
    
    return BEGIN;
}

void print_Poly(const Poly& poly) 
{
    int maxDeg = 0;
    for (int i = 10; i >= 0; i--)
    {
        if (poly[i] != 0) 
        {
            maxDeg = i;//找到最高次项
            break;
        }
    }

    if (maxDeg == 0 && poly[0] == 0) 
    {
        cout << "Runtime = 0" << endl;
        return;
    }

    cout << "Runtime = ";
    bool firstTerm = true;

    for (int deg = maxDeg; deg >= 0; deg--) 
    {
        long long coeff = poly[deg];
        if (coeff == 0) continue;

        if (firstTerm) 
        {
            if (coeff < 0) cout << "-";
            firstTerm = false;
        } 
        else 
        {
            if (coeff > 0) cout << "+";
            else cout << "-";
        }

        long long absCoeff = abs(coeff);

        if (deg == 0) 
        {
            cout << absCoeff;
        }
        else if (deg == 1) 
        {   if(absCoeff == 1) cout << "n";//系数为1时无需表示
            else
            cout << absCoeff << "*n";//1次无需表示
        } 
        else 
        {   if(absCoeff == 1) 
            cout << "n^" << deg;
            else
            cout << absCoeff << "*n^" << deg;
        }
    }
    cout << endl;
}


int main() 
{
    stack<StackFrame> loopStack;//利用栈存储loop
    Poly totalPoly(11, 0);
    loopStack.push({"BASE", constPoly(1)});//防止空栈

    string word;
    while (cin >> word) 
    {
        Type type = get_Type(word);

        switch (type) 
        {
            case BEGIN: 
            {
                Poly currPoly = loopStack.top().poly;
                loopStack.push({"BEGIN", currPoly});
                break;
            }
            case LOOP: 
            {
                string param;
                cin >> param;
                Poly loopPoly;

                if (param == "n") loopPoly = nPoly();
                else if (isNumber(param)) loopPoly = constPoly(stoll(param));

                Poly newPoly = poly_Mul(loopStack.top().poly, loopPoly);
                loopStack.push({"LOOP", newPoly});
                break;
            }
            case OP: 
            {
                long long num;
                cin >> num;
                Poly addPoly = polyMul_Const(loopStack.top().poly, num);//与当前栈顶进行常数运算
                totalPoly = poly_Add(totalPoly, addPoly);//加入到总耗时
                break;
            }
            case END: 
            {
                if (!loopStack.empty() && loopStack.top().type != "BASE") //弹出最后一个loop，循环次数回到上个loop
                {
                    loopStack.pop();
                }
                break;
            }
            default : break ;
           
        }
    }

    print_Poly(totalPoly);
    return 0;
}