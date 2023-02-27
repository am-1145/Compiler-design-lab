#include <bits/stdc++.h>
using namespace std;
vector<string> p(0);
bool datatype(string t)
{
    p = {"int", "string", "char", "char*", "bool", "float",
         "double", "long", "long long"};
    for (auto i : p)
        if (t == i)
            return true;
    return false;
}

bool keyword(string t)
{
    p = {"main", "if", "else", "for", "void", "return", "cin", "cout"};
    for (auto i : p)
        if (i == t)
            return true;
    return false;
}

bool op(string t)
{
    p = {"+", "-", "=", "&&", "||", "?", ":", "::", ">>", "<<"};
    for (auto i : p)
        if (i == t)
            return true;
    return false;
}
bool sep(string t)
{
    p = {",", ";"};
    for (auto i : p)
        if (t == i)
            return true;
    return false;
}

bool par(string t)
{
    p = {"{", "()", "}", "[]", "[", "]", "{}", "(", ")"};
    for (auto i : p)
        if (t == i)
            return true;
    return false;
}

bool id(string t)
{
    if (isalpha(t[0]) || t[0] == '_')
        return true;
    return false;
}
int main()
{
    string s, t = "";
    int cnt = 0, cnt_token = 0;
    vector<string> dt(0), idf(0);
    bool chk = 0, chkd = 1, eq = 0;
    ifstream myfile;
    myfile.open("temp.txt");
    // while(myfile){
    //     s=myfile.get();
    while (getline(myfile, s))
    {
        if (s.size() == 0)
        {
            break;
        }
        if (s[0] == '/' && s.size() > 1)
        {
            if (s[1] == '/')
                cout << s << " comment\n";
            else if (s[1] == '*')
            {
                t += s;
                chk = 1;
                if (s[s.size() - 1] == '/' && s[s.size() - 2] == '*')
                {
                    cout << t << " comment\n";
                    t = "";
                    chk = 0;
                }
            }
        }
        else if (chk)
        {
            t += s;
            if (s.back() == '/' && s[s.size() - 2] == '*')
            {
                cout << t << " comment\n";
                t = "";
                chk = 0;
            }
        }
        else
        {
            s.push_back(' ');
            for (auto i : s)
            {
                if (i != ' ')
                    t += i;
                else
                {
                    if (t.size())
                    {
                        if (datatype(t))
                        {
                            cout << t << " datatype\n", chkd = 1, cnt_token++;
                        }
                        else if (keyword(t))
                            cout << t << " keyword\n", cnt_token++;
                        else if (op(t))
                        {
                            cout << t << " operator\n", cnt_token++;
                            if (t == "=")
                                eq = 1;
                        }
                        else if (sep(t))
                            cout << t << " separator\n", cnt_token++;
                        else if (par(t))
                            cout << t << " parenthesis\n", cnt_token++;
                        else if (id(t))
                        {
                            if (chkd)
                            {
                                cout << t << " identifier\n", chkd = 0, cnt_token++;
                                idf.push_back(t);
                            }
                            else
                            {
                                bool c = 0;
                                for (auto i : idf)
                                {
                                    if (t == i)
                                    {
                                        c = 1, cnt_token++;
                                    }
                                }
                                if (!c)
                                    cout << t << " not a valid identifier\n";
                            }
                        }
                        else if (eq)
                        {
                            cout << t << " value\n", cnt_token++;
                            eq = 0;
                        }
                        else
                            cout << t << " invalid\n";
                        t = "";
                    }
                }
            }
        }
    }
    cout << "\n total number of tokens = " << cnt_token;
    return 0;
}