#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n;
    in >> n;
    std::vector<std::vector<int>> matr(n, std::vector<int>(n));
    for(int i = 0; i < n;i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp;
            in >> temp;
            matr[i][j] = temp;
        }
    }
    std::vector<int> marks(n);
    std::queue<int> q;
    q.push(0);
    int i = 1;
    int flag = 1;
    while(!q.empty())
    {
        int index = q.front();
        q.pop();
        if (marks[index] == 0)
        {
            marks[index] = i;
            i++;
            for (int j = 0; j < n;j++)
            {
                if (matr[index][j] == 1 && marks[j] == 0) q.push(j);
            }
        }
        if (q.empty())
        {
            while (flag < n)
            {
                if (marks[flag] == 0) 
                {
                    q.push(flag);
                    break;
                }
                flag++;
            }
        }
    }
    for (auto const& a: marks)
    {
        out << a << " ";
    }
}
