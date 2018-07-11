#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <map>
#include <set>
#include <climits>
#include <vector>

using std::string;
using std::cin;
using std::cout;
using std::endl;

typedef std::pair<int, int> pp;

const int maxn = 1005;  //最大不同字符个数
const int inf = INT_MAX;

std::map<char, int> CharCount;  //记录所有字符以及出现的次数
char book[maxn];                //记录第i个字符
string HuffDic[maxn];           //记录字符对应的哈夫曼码
bool ERROR = false;             //標記哈夫曼樹構造出錯
int n, m;

class Huffman {

private:
    int weight, parent, left, right;    //權值, 父結點, 左子結點, 右子結點
public:
    Huffman(int a = 0, int b = 0, int c = 0, int d = 0) : weight(a), parent(b), left(c), right(d) {}
    friend std::ostream & operator << (std::ostream &out, Huffman t) {
        out << t.weight << ' ' << t.parent << ' ' << t.left << ' ' << t.right << endl;
        return out;
    }
    friend pp Select(Huffman *tree, int x) {   //返回1-x中双亲为0且权值最小的两个节点的索引

        int s1 = inf, s2 = inf, id1 = 1, id2 = 2;
        for(int i = 1; i <= x; i++)
            if(!tree[i].parent and tree[i].weight < s1) {
                id1 = i;
                s1 = tree[i].weight;
            }
        for(int i = 1; i <= x; i++)
            if(i != id1 and !tree[i].parent and tree[i].weight < s2) {
                id2 = i;
                s2 = tree[i].weight;
            }
        return pp(id1, id2);
    }
    friend void Create_Huffman(Huffman *tree, string x) {

        for (char &i : x) CharCount[i]++;
        n = (int)CharCount.size();      //共有n個不同的字符

        if (n <= 1) {   //標記構造出錯
            ERROR = true;
            return;
        }
        ERROR = false;
        m = (n << 1) - 1;
        tree = new Huffman[m + 1];

        int ct = 0;
        for (auto &p : CharCount) {
            tree[++ct].weight = p.second;    //每個葉子結點的權值為對應字符出現的次數
            book[ct] = p.first;              //index -> CharName
        }

        for (int i = n + 1; i <= m; i++) {
            auto s = Select(tree, i - 1);
            tree[s.first].parent = tree[s.second].parent = i;
            tree[i].left = s.first;         //左子樹為未標記的權值最小結點
            tree[i].right = s.second;       //右子樹為未標記的權值第二小結點
            tree[i].weight = tree[s.first].weight + tree[s.second].weight;  //新結點的權值為兩子樹權值之和
        }

        for (int i = 1, fa, now; i <= n; i++) {   //求葉子結點的哈夫曼編碼
            x.clear();
            now = i;
            do {
                fa = tree[now].parent;
                if (now == tree[fa].left) x += '0';
                else x += '1';
                now = fa;
            } while (fa);
            reverse(x.begin(), x.end());
            HuffDic[i] = x;
        }
        puts("編碼成功！編碼表如下：");
        for (int i = 1; i <= n; i++) {
            cout << book[i] << " -> " << HuffDic[i] << endl;
        }
    }
};
void Coding() {  //对某一字符串进行编码

    puts("輸入待編碼的字符串");
    string x;
    getline(cin, x);
    for (int i = 0; i < x.length(); i++)
        if (CharCount.count(x[i])) {
            for (int j = 1; j <= n; j++)
                if (book[j] == x[i]) {
                    cout << HuffDic[j];
                    break;
                }
        } else {
            puts("\n編碼表中不存在該字符");
            return;
        }
    puts("");
}

void Decoding() { //对某个零一字符串进行译码

    puts("輸入待譯碼的二進制碼");
    string x;
    getline(cin, x);
    int len = (int)x.length(), all = 0;
    string y;
    for (int i = 0; i < len; i++) {
        y += x[i];
        for (int j = 1; j <= n; j++)
            if (HuffDic[j] == y) {
                all += y.length();
                putchar(book[j]);
                y.clear();
                break;
            }
    }
    if (all < len) puts(" (二進制不規範，譯碼不成功)");
    puts("");
}

int main() {

    string x;
    Huffman *tree = nullptr;
    int choose;

    restart:
    puts("請輸入任意字符串以便初始化：");
    getline(cin, x);
    Create_Huffman(tree, x);
    if(ERROR) {
        puts("輸入有誤, 請重新輸入！");
        goto restart;
    }

    puts("選擇接下來的操作：退出->0, 編碼->1, 譯碼->2");
    while (cin >> choose and choose) {
        getchar();
        if (!choose) return 0;
        else if (choose == 1) Coding();
        else if (choose == 2) Decoding();
        else {
            puts("輸入有誤");
            continue;
        }
        puts("選擇接下來的操作：退出->0, 編碼->1, 譯碼->2");
    }
    
    return 0;
}
/*
abbbbccddd
aabbbccccddddddddd
 */
