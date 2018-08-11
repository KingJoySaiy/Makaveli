#include <bits/stdc++.h>

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)
#define ALL(x) (x).begin(), (x).end()

const int max_N = 14;
const int max_S = (1 << max_N);

int T, n, s;

std::vector<int> vec[max_S];

int winner[max_S << 1];

int race(int a, int b) {
    int winner = vec[a].back() > vec[b].back() ? a : b;
    int loser = a ^ b ^ winner;
    auto it = std::upper_bound(ALL(vec[winner]), vec[loser].back());
    vec[winner].erase(it);
    return winner;
}

void testCase() {
    static int caseID = 0;
    scanf("%d", &n);
    s = (1 << n);
    for (int i = 0; i < s; ++i) {
        vec[i].resize(n);
        for (int j = 0; j < n; ++j) {
            scanf("%d", &vec[i][j]);
        }
        std::sort(ALL(vec[i]));
    }
    for (int i = 0; i < s; ++i) {
        winner[s + i] = i;
    }
    for (int i = s - 1; i; --i) {
        winner[i] = race(winner[ls(i)], winner[rs(i)]);
    }
    printf("Case #%d: %d\n", ++caseID, winner[1] + 1);
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
