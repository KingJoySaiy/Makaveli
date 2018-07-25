#include <bits/stdc++.h>

using namespace std;
long long n, ct;

int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) {
        cin >> n;
        cout << (n % 3 ? (n % 4 ? -1 : (n * n * n / 32)) : (n * n * n / 27)) << endl;
    }

    return 0;
}

