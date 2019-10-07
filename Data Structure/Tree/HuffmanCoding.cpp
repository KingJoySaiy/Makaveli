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

const int maxn = 1005;  //max size of different characters
const int inf = INT_MAX;

std::map<char, int> CharCount;  //amount of each character
char book[maxn];                //save i-th character
string HuffDic[maxn];           //huffman code of the i-th character
bool ERROR = false;
int n, m;

class Huffman {

private:
    int weight, parent, left, right;    //weight, parent id, left-child id, right-child id
public:
    Huffman(int a = 0, int b = 0, int c = 0, int d = 0) : weight(a), parent(b), left(c), right(d) {}
    friend std::ostream & operator << (std::ostream &out, Huffman t) {
        out << t.weight << ' ' << t.parent << ' ' << t.left << ' ' << t.right << endl;
        return out;
    }
    friend pp Select(Huffman *tree, int x) {   //return 2 index of nodes whose parent valued 0 & have minimum weight(range [1, x])

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
        n = (int)CharCount.size();      //n different characters

        if (n <= 1) {   //mark error when n <= 1
            ERROR = true;
            return;
        }
        ERROR = false;
        m = (n << 1) - 1;
        tree = new Huffman[m + 1];

        int ct = 0;
        for (auto &p : CharCount) {
            tree[++ct].weight = p.second;    //weight defined as number of occurence of each character
            book[ct] = p.first;              //index -> CharName
        }

        for (int i = n + 1; i <= m; i++) {
            auto s = Select(tree, i - 1);
            tree[s.first].parent = tree[s.second].parent = i;
            tree[i].left = s.first;         //left child is minimum node
            tree[i].right = s.second;       //right child is 2nd minimun node
            tree[i].weight = tree[s.first].weight + tree[s.second].weight;  //weight of new node is sum of its 2 children's weight
        }

        for (int i = 1, fa, now; i <= n; i++) {   //calculate huffman-code of each leaf node
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
        puts("encode successful! the table is shown below:");
        for (int i = 1; i <= n; i++) {
            cout << book[i] << " -> " << HuffDic[i] << endl;
        }
    }
};
void Coding() {  //encode a string

    puts("please input a string to encode");
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
            puts("\nexist invalid character!");
            return;
        }
    puts("");
}

void Decoding() { //decode binary code consist of '0' or '1'

    puts("input binary code to decode: ");
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
    if (all < len) puts("invalid binary code, fail to decode!");
    puts("");
}

int main() {

    string x;
    Huffman *tree = nullptr;
    int choose;

    restart:
    puts("please input any string to initialize: ");
    getline(cin, x);
    Create_Huffman(tree, x);
    if(ERROR) {
        puts("invalid input! please try again!");
        goto restart;
    }

    puts("select next operation: exit->0, encode->1, decode->2");
    while (cin >> choose and choose) {
        getchar();
        if (!choose) return 0;
        else if (choose == 1) Coding();
        else if (choose == 2) Decoding();
        else {
            puts("invalid input! please try again!");
            continue;
        }
        puts("select next operation: exit->0, encode->1, decode->2");
    }
    
    return 0;
}
/*
abbbbccddd
aabbbccccddddddddd
 */
