#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

int main() {

    for (LL n = 1; n <= 100; n++) {
        cout << n << ' ';
        vector<int> a;
        set<tuple<int, int, int>> b;
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                a.push_back(i);
                a.push_back(n / i);
            }
        }

        LL res = LL(-1e18);
        tuple<int, int, int> ppp;
        for (int i = 0; i < a.size(); i++)
            for (int j = 0; j < a.size(); j++) {
                for (int k = 0; k < a.size(); k++) {
                    if (a[i] + a[j] + a[k] == n) {
                        int x[] = {a[i], a[j], a[k]};
                        sort(x, x + 3);
                        if (b.find(tie(x[0], x[1], x[2])) == b.end()) {
                            if (LL(x[0]) * x[1] * x[2] > res) {
                                res = LL(x[0]) * x[1] * x[2];
                                ppp = tie(x[0], x[1], x[2]);
                            }
                            b.insert(tie(a[i], a[j], a[k]));
                        }
                    }
                }
            }
        if (res == 1e18) cout << -1;
        else cout << '(' << get<0>(ppp) << ',' << get<1>(ppp) << ',' << get<2>(ppp) << ')';
        cout << endl;
    }


    return 0;
}

