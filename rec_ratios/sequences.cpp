#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main()
{
    int count;
    cin >> count;
    vector<int> A(count + 1), B(count + 1);
    vector<vector<int>> dp(count + 1, vector<int>(count + 1));
    for (int i = 1; i <= count; i++)
    {
        cin >> A[i];
    }
    for (int i = 1; i <= count; i++)
    {
        cin >> B[i];
    }
    for (int i = 1; i <= count; i++)
    {
        for (int j = 1; j <= count; j++)
        {
            if (A[i] == B[j])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    set<int> Aind, Bind;
    int i = count;
    int j = count;
    while (i > 0 || j > 0)
    {
        if (A[i] == B[j]) 
        {
            Aind.insert(--i);
            Bind.insert(--j);
        }
        else 
        {
            if (dp[i][j] == dp[i][j - 1]) j--;
            else i--;
        }
    }
    cout << dp[count][count] << endl;
    for (int a: Aind) cout << a << " ";
    cout << endl;
    for (int a: Bind) cout << a << " ";
}