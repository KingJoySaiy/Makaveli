#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5 + 5);
int n, m;

struct data {

    double x, y, res;
    int id;
    bool operator < (data t) {
        return x < t.x or x == t.x and y < t.y;
    }
    double K(data t) {
        return (y - t.y) / (x - t.x);
    }
    double cross(data a,data b) {    //t->a cross t->b
        return (a.x - x) * (b.y - y) - (a.y - y) * (b.x - x);
    }
} a[maxn], s[maxn];

inline bool cmp(data a, data b) {

    return a.id < b.id;
}
void graham() {

    for (int i = 0, top = 0; i < m; i++) {
        if (!a[i].id) {      //id -> 0 ~ n - 1，加入凸包
            while (top > 1 and s[top - 2].cross(a[i], s[top - 1]) <= 0) top--;
            s[top++] = a[i];
        } else {              //id -> n ~ m - 1，在凸包中三分斜率最小值
            if (!top) continue;
            int l = 0, r = top - 1, m;
            while (l < r) {
                m = (l + r) / 2;
                if (a[i].K(s[m]) < a[i].K(s[m + 1])) r = m;
                else l = m + 1;
            }
            a[i].res = min(a[i].res, a[i].K(s[l]));
        }
    }
}
int main() {

    cin >> n;
    for (int i = 0; i < n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
    cin >> m;
    m += n;
    for (int i = n; i < m; i++)
        scanf("%lf%lf", &a[i].x, &a[i].y), a[i].id = i;

    sort(a, a + m);
    graham();
    reverse(a, a + m);
    graham();
    sort(a, a + m, cmp);

    for (int i = n; i < m; i++) {
        if (a[i].res < 0) printf("%.12f\n", -1 * a[i].res);
        else puts("No cross");
    }

    return 0;
}