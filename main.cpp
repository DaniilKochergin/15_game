#include <iostream>
#include "Pyatnatshki.h"

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<unsigned >> v(n, vector<unsigned>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            v[i][j] = i*n + j+1;
        }
    }
    swap(v[n-1][n-2], v[n-1][n-3]);
    v[n-1][n-1] = 0;
    Board a(v);
    // vector<vector<unsigned>> v(n,vector<unsigned > (n));

    cout << a << endl;
    cout<<a.is_solvable()<<endl;
    return 0;
}