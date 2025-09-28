#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int solomove(const vector<int> &cards, int len, int j)
{
    int sum = 0, first = j - len + 1;
    while (first != j)
    {
        sum += abs(cards[first] - cards[j]);
        first++;
    }
    return sum;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int count;
    in >> count;
    vector<int> cards(count + 1, 0);
    for (int i = 1; i <= count; i++)
    {
        int temp;
        in >> temp;
        cards[temp] = i;
    }
    vector<vector<int>> dp(count + 1, vector<int>(count + 1));
    for (int len = 2; len <= count; len++)
    {
        for (int i = 1, j = len; j <= count; j++, i++)
        {       
            int min_p = solomove(cards, len, j);
            for (int imove = i + 1, jmove = j - len + 1; jmove < j; imove++, jmove++)
            {
                int podposled = dp[imove][j] + dp[i][jmove] + abs(cards[jmove] - cards[j]);
                min_p = min(podposled, min_p);
            }
            dp[i][j] = min_p;
        }
    }

    out << dp[1][count];

    /*for (vector<int> v: dp)
    {
        for (int a: v)
        {
            cout << a << "\t";
        }
        cout << endl;
    } */
}