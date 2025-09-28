#include <iostream>
#include <fstream>
#include <set>
#include <string>

using namespace std;

int main() {
    set<int> s;
    ifstream input("input.txt");
    ofstream output("output.txt");
    string line;
    while(getline(input, line)) {
        int a = stoi(line);
        s.insert(a);
    }
    long long sum = 0;
    for (int a: s) {
        sum += a;
    }
    output << sum;
}