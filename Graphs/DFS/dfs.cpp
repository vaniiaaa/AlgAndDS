#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n;
    in >> n;
    std::vector<std::vector<int>> matr(n, std::vector<int>(n));
    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp;
            in >> temp;
            matr[i][j] = temp;
        }
    }
    std::vector<int> marks(n, 0);
    std::stack<int> st;
    st.push(0);
    int i = 1;
    int flag = 1;
    while(!st.empty())
    {
        int index = st.top();
        st.pop();
        if (marks[index] == 0)
        {
            marks[index] = i;
            i++;
            for (int j = n - 1; j >=0; j--)
            {
                if (matr[index][j] == 1 && marks[j] == 0) st.push(j);
            }
        }
        if (st.empty())
        {
            while (flag < n)
            {
                if (marks[flag] == 0) 
                {
                    st.push(flag);
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
