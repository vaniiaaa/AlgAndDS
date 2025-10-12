#include <iostream>
#include <vector>

static int mod = 1000000007;
using namespace std;

long long BinExp(long long a, long long n) 
{
    if (n == 0) return 1;
    if (n == 1) return a % mod;
    long long t = BinExp(a, n >> 1);
    t = (t * t) % mod;
    if ((n & 1) == 0) 
        return t;
    else 
        return (t * a) % mod;
}

int main()
{
    int N, K;
    cin >> N >> K;
    
    if (K > N) 
    {
        cout << 0;
        return 0;
    }
    
    if (K > N - K) {
        K = N - K;
    }
    
    long long top = 1, bott = 1;
    for (int i = 1; i <= K; i++) 
    {
        top = (top * (N - i + 1)) % mod;
        bott = (bott * i) % mod;
    }
    
    long long res = (top * BinExp(bott, mod - 2)) % mod;
    cout << res;
    
    return 0;
}