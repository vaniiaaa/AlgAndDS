#include <iostream>
#include <vector>

using namespace std;


void BinarySearch(const vector<int>& arr, int x, int& res, int& b, int& l) {
    int n = arr.size();
    
    int left = 0, right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    b = left;
    
    left = 0, right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    l = left;
    
    res = (b < n && arr[b] == x) ? 1 : 0;
}
int main() {
    
    int n;
    cin >> n;
    vector<int> M1(n);
    for (int i = 0; i < n; i++) {
        cin >> M1[i];
    }
    
    int k;
    cin >> k;
    vector<int> M2(k);
    for (int i = 0; i < k; i++) {
        cin >> M2[i];
    }

    for (int i = 0; i < k; i++) {
        int b, l, res;
        BinarySearch(M1, M2[i], res, b, l);
        cout << res << " " << b << " " << l << "\n";
    }
    
    return 0;
}