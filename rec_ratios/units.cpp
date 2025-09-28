#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

int binRec(int n, int k, vector<vector<int>>& table) 
{
    if (k == 0 || k == n) return 1;
    if (k == 1 || k == n - 1) return n;
    if (k > n - k) k = n - k;
    
    if (table[n][k] != -1) return table[n][k];
    
    int result = (binRec(n - 1, k - 1, table) + binRec(n - 1, k, table)) % MOD;
    table[n][k] = result;
    return result;
}

int find(int N, int K) 
{
    if (K < 0 || K > N) return 0;
    if (K == 0 || K == N) return 1;
    if (K > N - K) K = N - K;

    vector<vector<int>> table(N + 1, vector<int>(K + 1, -1));
    
    return binRec(N, K, table);
}

int findDP(int N, int K) 
{
    if (K < 0 || K > N) return 0;
    if (K > N - K) K = N - K;

    vector<int> dp(K + 1, 0);
    dp[0] = 1;
    
    for (int i = 1; i <= N; i++) 
    {
        for (int j = min(i, K); j > 0; j--) 
        {
            dp[j] = (dp[j] + dp[j - 1]) % MOD;
        }
    }
    
    return dp[K];
}

int main()
{
    int N, K;
    cin >> N >> K;
    cout << find(N, K);
}