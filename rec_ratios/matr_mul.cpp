#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class matr
{
public:
    matr(int n1, int n2) : rows(n1), cols(n2) {}
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    friend ostream &operator<<(ostream &out, const matr &m)
    {
        out << m.rows << " " << m.cols;
        return out;
    }

private:
    int rows, cols;
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int s;
    vector<matr> mat;
    in >> s;
    for (int i = 0; i < s; i++)
    {
        int n1, n2;
        in >> n1 >> n2;
        matr temp(n1, n2);
        mat.push_back(temp);
    }
    vector<vector<int>> dp(s, vector<int>(s, 0));
    for (int len = 2; len <= s; len++)
    {
        for (int i = 0; i <= s - len; i++)
        {
            int j = i + len - 1;
            dp[i][j] = 2147483647;
            for (int k = i; k < j; k++)
            {
                int q = dp[i][k] + dp[k + 1][j] + mat[i].getRows() * mat[k].getCols() * mat[j].getCols();
                if (q < dp[i][j])
                    dp[i][j] = q;
            }
        }
    }
    out << dp[0][s - 1] << endl;
}