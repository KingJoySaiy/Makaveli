#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <utility>
#include <string>
#include <vector>
#include <map>

using namespace std;

const int maxn = 1005;  //���ͬ�ַ�����

struct Huffman {

    int weight, parent, left, right;
    Huffman(int a = 0, int b = 0, int c = 0, int d = 0) : weight(a), parent(b), left(c), right(d) {}
    friend ostream & operator << (ostream &out, Huffman t) {
        out << t.weight << ' ' << t.parent << ' ' << t.left << ' ' << t.right << endl;
        return out;
    }
};
map<char,int> all_char;     //��¼�����ַ��Լ����ֵĴ���
char book[maxn];            //��¼��i���ַ�
string huff_dic[maxn];      //��¼�ַ���Ӧ�Ĺ�������
int n, m;

pair<int,int> Select(Huffman *tree, int x) {   //����1-x��˫��Ϊ0��Ȩֵ��С�������ڵ������

    int s1 = INT_MAX, s2 = INT_MAX;
    int id1 = 1, id2 = 2;
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
    return make_pair(id1, id2);
}
void Create_Huffman(Huffman *tree,string x) {

    for(int i = 0; i < x.length(); i++) all_char[x[i]]++;
    n = all_char.size();      //����n����ͬ���ַ�

    if(n <= 1) return;
    m = (n << 1) - 1;
    tree = new Huffman[m + 1];

    int ct = 0;
    for(auto p = all_char.begin(); p != all_char.end(); p++) {
        tree[++ct].weight = (*p).second;    //ÿ��Ҷ�ӽڵ��ȨֵΪ��Ӧ�ַ����ֵĴ���
        book[ct] = (*p).first;
    }

    for(int i = n + 1; i <= m; i++) {
        pair<int,int> s = Select(tree, i-1);
        tree[s.first].parent = tree[s.second].parent = i;
        tree[i].left = s.first;
        tree[i].right = s.second;
        tree[i].weight = tree[s.first].weight + tree[s.second].weight;
    }

    for(int i = 1, fa, now; i <= n; i++) {   //��Ҷ�ӽڵ�Ĺ���������
        x.clear();
        now = i;
        do {
            fa = tree[now].parent;
            if(now == tree[fa].left) x += '0';
            else x += '1';
            now = fa;
        } while(fa);
        reverse(x.begin(),x.end());
        huff_dic[i] = x;
    }
    puts("����ɹ�����������£�");
    for(int i = 1; i <= n; i++)
        cout << book[i] << " -> " << huff_dic[i] << endl;
}
void Coding() {  //��ĳһ�ַ������б���

    puts("�����������ַ���");
    string x;
    getline(cin,x);
    for(int i = 0; i < x.length(); i++)
        if(all_char.count(x[i])) {
            for(int j = 1; j <= n; j++)
                if(book[j] == x[i]) {
                    cout << huff_dic[j];
                    break;
                }
        } else {
            puts("\n������в����ڸ��ַ�");
            return;
        }
    puts("");
}
void Decoding() { //��ĳ����һ�ַ�����������

    puts("���������Ķ�������");
    string x;
    getline(cin,x);
    int len = x.length(), all = 0;
    string y;
    for(int i = 0; i < len; i++) {
        y += x[i];
        for(int j = 1; j <= n; j++)
            if(huff_dic[j] == y) {
                all += y.length();
                putchar(book[j]);
                y.clear();
                break;
            }
    }
    if(all < len) puts(" (�������벻�淶,���벻�ɹ�)");
    puts("");
}
int main() {

    string x;
    Huffman *tree;
    int choose;

    puts("�����������ַ����Ա��ʼ����");
    getline(cin,x);
    Create_Huffman(tree,x);

    puts("ѡ��������Ĳ������˳�->0, ����->1, ����->2");
    while(cin>>choose and choose) {
        getchar();
        if(!choose) return 0;
        else if(choose == 1) Coding();
        else if(choose == 2) Decoding();
        else {
            puts("��������");
            continue;
        }
        puts("ѡ��������Ĳ������˳�->0, ����->1, ����->2");
    }

//    system("pause");
    return 0;
}
/*
abbbbccddd
 */
