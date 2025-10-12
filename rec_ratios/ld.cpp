#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    int x, y, z;
    in >> x >> y >> z;
    std::string a, b;
    in.ignore();
    std::getline(in, a);
    std::getline(in, b);

    int asize = a.size();
    int bsize = b.size();
    std::vector<std::vector<int>> dp(asize + 1, std::vector<int>(bsize + 1));
    for (int i = 0; i <= asize; i++) 
        dp[i][0] = i * x;
    for (int j = 0; j <= bsize; j++) 
        dp[0][j] = j * y;
    for (int i = 1; i <= asize; i++)
    {
        for (int j = 1; j <= bsize; j++)
        {
            dp[i][j] = std::min(std::min(dp[i - 1][j] + x, dp[i][j - 1] + y), dp[i - 1][j - 1] + z * ((a[i - 1] == b[j - 1]) ? 0 : 1));
        }
    }
    out << dp[asize][bsize];
}