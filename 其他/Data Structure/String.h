#ifndef INC_233_STRING_H
#define INC_233_STRING_H

#include <iostream>
#include <cstring>

using std::ostream;
using std::istream;

class String {

private:
    char *str;
    size_t len;
    static int num_strings;
    static const int CINLIM = 80;   //cin input limit

public:
    //constructors and destructors
    String() {
        
        len = 4;
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

    //overloaded operator methods
    String & operator = (const String &st) {

        if (this == &st) return *this;
        delete[] str;
        len = st.len;
        str = new char[len + 1];
        strcpy(str, st.str);
        return *this;
    }
    String & operator = (const char *s) {
        
        delete[] str;
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
        return *this;
    }
    char & operator [] (int i) {
        
        return str[i];
    }
    const char & operator [] (int i) const {

        return str[i];
    }

    //overloaded operator friends
    friend bool operator < (const String &st1, const String &st2);
    friend bool operator > (const String &st1, const String &st2);
    friend bool operator == (const String &st1, const String &st2);
    friend ostream & operator << (ostream &os, const String &st);
    friend istream & operator >> (istream &is, String &st);

    //static function
    static int HowMany();
};

//overload operator friends
bool operator<(const String &st1, const String &st2) {

    return strcmp(st1.str, st2.str) < 0;
}

bool operator>(const String &st1, const String &st2) {

    return st2.str < st1.str;
}

bool operator==(const String &st1, const String &st2) {

    return strcmp(st1.str, st2.str) == 0;
}

//simple String output
ostream &operator<<(ostream &os, const String &st) {

    os << st.str;
    return os;
}

istream & operator >> (istream &is, String &st) {

    char tmp[String::CINLIM];
    is.get(tmp, String::CINLIM);
    if (is) st = tmp;
    while (is and is.get() != '\n');
    return is;
}

//static method
int String::HowMany() {

    return num_strings;
}
int String::num_strings = 0;


#endif //INC_233_STRING_H
