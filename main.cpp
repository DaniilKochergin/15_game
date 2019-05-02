#include <iostream>
#include "Board.h"
#include "Solver.h"

using namespace std;

int main() {
    int n;
    cin >> n;
    std::vector<vector<unsigned>> z = {{2, 6,  3,  4},
                                       {1, 7,  11, 8},
                                       {5, 10, 0,  12},
                                       {9, 13, 14, 15}};
    Board a(n);
    Solver s(a);
    cout << s.data.size() << endl;
    for (size_t i = 0; i < s.data.size(); ++i) {
        cout << s.data[i] << endl;
    }
    return 0;
}