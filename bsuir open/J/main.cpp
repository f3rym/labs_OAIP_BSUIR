#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    string target = "BSUIROPEN";
    int count[1000] = {0};     

    string s;
    getline(cin, s); 

    int total_upper = 0;
    for (char c : s)
    {
        if (isupper(c)) 
        {
            count[c]++;    
            total_upper++; 
        }
    }

    for (char c : target)
    {
        if (count[c] < 1)
        {
            cout << "-1";
            return 0;
        }
    }

    int needed_chars = target.size();

    int extra_chars = total_upper - needed_chars;


    int ans = 0;
    while (extra_chars > 0)
    {
        int power = 1;
        while (power * 2 <= extra_chars)
        {
            power *= 2;
        }
        extra_chars -= power; 
        ans++;            
    }

    cout << ans; 
    return 0;
}
