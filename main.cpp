#include <iostream>
#include "15_game.h"

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
    for (auto &it : s) {
        cout << it << endl;
    }
    return 0;
}