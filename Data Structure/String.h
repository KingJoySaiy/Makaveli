#ifndef INC_233_STRING_H
#define INC_233_STRING_H

#include <iostream>
#include <cstring>

using std::ostream;
using std::istream;

/******** String (imitate std::string) ********/
class String {
private:
    char *str;
    size_t len;
    static int num_strings;
    static const int CINLIM = 80;   //cin input limit
public:
    String() {    //constructors and destructors
        len = 0;
        str = new char[1];
        str[0] = '\0';
        num_strings++;
    }

    String(const char *s) {
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
        num_strings++;
    }

    String(const String &st) {
        num_strings++;
        len = st.len;
        str = new char[len + 1];
        strcpy(str, st.str);
    }

    ~String() {
        --num_strings;
        delete[] str;
    }

    size_t Length() const {
        return len;
    }

    String &operator=(const String &st) {    //overloaded operator methods
        if (this == &st) return *this;
        delete[] str;
        len = st.len;
        str = new char[len + 1];
        strcpy(str, st.str);
        return *this;
    }

    String &operator=(const char *s) {
        delete[] str;
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
        return *this;
    }

    char &operator[](int i) {
        return str[i];
    }

    const char &operator[](int i) const {
        return str[i];
    }

    friend bool operator<(const String &st1, const String &st2);    //overloaded operator friends
    friend bool operator>(const String &st1, const String &st2);

    friend bool operator==(const String &st1, const String &st2);

    friend ostream &operator<<(ostream &os, const String &st);

    friend istream &operator>>(istream &is, String &st);

    static int HowMany();    //static function
};

bool operator<(const String &st1, const String &st2) {    //overload operator friends
    return strcmp(st1.str, st2.str) < 0;
}

bool operator>(const String &st1, const String &st2) {
    return st2.str < st1.str;
}

bool operator==(const String &st1, const String &st2) {
    return strcmp(st1.str, st2.str) == 0;
}

ostream &operator<<(ostream &os, const String &st) {    //simple String output/input
    os << st.str;
    return os;
}

istream &operator>>(istream &is, String &st) {
    char tmp[String::CINLIM];
    is.get(tmp, String::CINLIM);
    if (is) st = tmp;
    while (is and is.get() != '\n');
    return is;
}

int String::HowMany() {    //static method
    return num_strings;
}

int String::num_strings = 0;

/******** String (length never changed)********/
#define maxn 255    //maxnLength, exceeded part should be cut
#define ERROR 0
#define OK true

typedef unsigned char sstring[maxn + 1];    //0 -> string length

bool strcat(sstring &res, sstring &a, sstring &b) {    //Concatenate a & b, return whether not cut

    int id = 1;
    if (a[0] + b[0] <= maxn) {    //not cut
        for (int i = 1; i < a[0]; i++) {
            res[id++] = a[i];
        }
        for (int i = 1; i < b[0]; i++) {
            res[id++] = a[i];
        }
        res[0] = id;
        return true;
    }
    if (a[0] < maxn) {    //cut b
        for (int i = 1; i < a[0]; i++) {
            res[id++] = a[i];
        }
        for (int i = 1; id <= maxn; i++) {
            res[id++] = b[i];
        }
        res[0] = maxn;
        return false;
    }

    //only cut a(b never used)
    for (int i = 1; i <= maxn; i++) {
        res[id++] = a[i];
    }
    res[0] = maxn;
    return false;
}

bool substr(sstring &res, sstring x, int id, int len) { //find sub-string of x begin from id to (id + len)

    if (id < 1 or id > x[0] or len < 0 or id + len - 1 > x[0]) return ERROR;
    for (int i = id, p = 1; i < id + len; i++) {
        res[p++] = x[i];
    }
    res[0] = len;
    return OK;
}

void init_next(sstring x, int next[]) {	//initiate next-array used in KMP-algorithm
	
	int i = 1, j = 0;
	next[1] = 0;
	while (i < x[0]) {
		if (!j or x[i] == x[j]) {
			i++;
			j++;
			if (x[i] != x[j]) next[i] = j;
			else next[i] = next[j];
		} else j = next[j];
	}
}

/******** KMP Algorithm ********/
int KMP(sstring s, sstring x, int next[], int id) {	//find 1st position x appears in s, after id-index
	
	int i = id, j = 1;
	while (i <= s[0] and j <= x[0]) {
		if  (j == 0 or s[i] == x[j]) {
			i++;
			j++;
		} else j = next[j];
	}
	if (j > x[0]) return i - x[0];
	return ERROR;
}

#undef maxn
#undef ERROR
#undef OK

#endif //INC_233_STRING_H






