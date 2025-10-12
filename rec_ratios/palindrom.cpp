#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
    std::string A;
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    std::getline(in, A);
    std::string B(A);
    std::reverse(B.begin(), B.end());
    A.insert(A.begin(), 1, ' ');
    B.insert(B.begin(), 1, ' ');
    int size = A.size();
    std::vector<std::vector<int>> dp(size + 1, std::vector<int>(size + 1));

    

    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (A[i] == B[j])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    std::string res;
    int i = size, j = size;
    while (i > 0 || j > 0)
    {
        if (A[i] == B[j]) 
        {
            res += A[i];
            i--;
            j--;
        }
        else 
        {
            if (dp[i][j] == dp[i][j - 1]) j--;
            else i--;
        }
    }
    out << res.size() - 1 << std::endl;
    out << res.substr(1, res.size() - 1);
}