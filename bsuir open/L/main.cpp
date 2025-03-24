#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;

const int MOD = 1000000007;

vector<int> getDivisors(int n)
{
    vector<int> divisors;
    for (int i = 1; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            divisors.push_back(i);
            if (i != n / i)
            {
                divisors.push_back(n / i);
            }
        }
    }
    return divisors;
}

long long solveRec(const vector<pair<char, int>> &vars, int idx, long long current)
{
    if (idx == vars.size())
    {
        return (current == 1) ? 1 : 0;
    }
    long long ways = 0;
    int freq = vars[idx].second;

    vector<int> divisors = getDivisors(current);

    for (int d : divisors)
    {
        long long factor = 1;
        for (int i = 0; i < freq; ++i)
        {
            if (factor > current)
                break; 
            factor *= d;
        }
        if (factor <= current && current % factor == 0)
        {
            ways = (ways + solveRec(vars, idx + 1, current / factor)) % MOD;
        }
    }
    return ways;
}

int main()
{
    char s[1000];
    if (!fgets(s, sizeof(s), stdin))
    {
        return 1;
    }
    s[strcspn(s, "\n")] = 0;

    char *eq = strchr(s, '=');
    if (!eq)
    {
        cerr << "Неверный формат ввода\n";
        return 1;
    }
    string left(s, eq - s);
    string right(eq + 1);

    vector<string> leftFactors, rightFactors;
    {
        int start = 0;
        while (true)
        {
            int pos = left.find('*', start);
            if (pos == string::npos)
            {
                leftFactors.push_back(left.substr(start));
                break;
            }
            leftFactors.push_back(left.substr(start, pos - start));
            start = pos + 1;
        }
    }
    {
        int start = 0;
        while (true)
        {
            int pos = right.find('*', start);
            if (pos == string::npos)
            {
                rightFactors.push_back(right.substr(start));
                break;
            }
            rightFactors.push_back(right.substr(start, pos - start));
            start = pos + 1;
        }
    }

    long long fixedLeft = 1;
    unordered_map<char, int> varCount;
    for (auto &factor : leftFactors)
    {
        if (factor.size() == 1 && isdigit(factor[0]))
        {
            fixedLeft *= (factor[0] - '0');
        }
        else
        {
            for (char c : factor)
            {
                if (isalpha(c))
                {
                    varCount[c]++;
                }
            }
        }
    }

    long long fixedRight = 1;
    for (auto &factor : rightFactors)
    {
        if (factor.size() == 1 && isdigit(factor[0]))
        {
            fixedRight *= (factor[0] - '0');
        }
        else
        {
            for (char c : factor)
            {
                if (isdigit(c))
                {
                    fixedRight *= (c - '0');
                }
            }
        }
    }

    if (fixedLeft == 0 || fixedRight % fixedLeft != 0)
    {
        cout << "0\n";
        return 0;
    }
    long long target = fixedRight / fixedLeft;

    if (varCount.empty())
    {
        cout << (target == 1 ? "-1" : "0") << "\n";
        return 0;
    }

    vector<pair<char, int>> vars;
    for (auto &p : varCount)
    {
        vars.push_back(p);
    }

    long long ans = solveRec(vars, 0, target);
    cout << ans % MOD << "\n";
    return 0;
}
