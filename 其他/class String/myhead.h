#include<iostream>
using std::ostream;
using std::istream;

#ifndef STRING_MYHEAD_H
#define STRING_MYHEAD_H

class String{

private:
    char *str;
    int len;
    static int num_strings;
    static const int CINLIM=80;//cin input limit
public:

    //constructors and other methods
    String(const char* s);
    String();
    String(const String&);
    ~String();
    int length()const { return len;}

    //overloaded operator methods
    String &operator=(const String &);
    String &operator=(const char*);
    char &operator[](int i);
    const char &operator[](int i)const;

    //overloaded operator friends
    friend bool operator<(const String &st1,const String &st2);
    friend bool operator>(const String &st1,const String &st2);
    friend bool operator==(const String &st1,const String &st2);
    friend ostream &operator <<(ostream &os,const String &st);
    friend istream &operator >>(istream &is,String &st);

    //static function
    static int HowMany();

};

#endif // MYHEAD_H_INCLUDED

