#include <cstdlib>
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int n;
    cin >> n;

    for (int x = 0; x < n; x++) {
        if (x + x + x + 3 == n) {
            cout << x + 2 << " " << x + 1 << " " << x << endl;
            exit(0);
        }
    }
    cout << -1 << endl;
    return 0;
}
