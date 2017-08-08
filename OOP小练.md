# 学生成绩
描述:建立一个学生情况登记表，包括学号、姓名、5门课成绩，实现如下功能:
1. 输入n个学生的数据
2. 计算每个学生的总分
3. 按每个学生总分由高到低排序
4. 查询给定学号的学生信息
## 一、面向过程设计(C)
```c++
#include<stdio.h>
typedef struct{

    int num,b[5],sum;
    char s[100];
}data;
void sort(data *a,int n){

    int i,j;
    for(i=0;i<n-1;i++)
        for(j=0;j<n-1-i;j++)
            if(a[j].sum<a[j+1].sum){
                data t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
}
void show(data x){

    int j;
    printf("%d %s",x.num,x.s);
    for(j=0;j<5;j++) printf(" %d",x.b[j]);
    printf(" %d\n",x.sum);
}
int main(){

    int n,x,i,j;
    data a[45];
    scanf("%d",&n);
    for(i=0;i<n;i++){
        a[i].sum=0;
        scanf("%d%s",&a[i].num,a[i].s);
        for(j=0;j<5;j++){
            scanf("%d",&a[i].b[j]);
            a[i].sum+=a[i].b[j];
        }
    }
    sort(a,n);
    for(i=0;i<n;i++) show(a[i]);
    
    scanf("%d",&x);
    for(i=0;i<n;i++)
        if(a[i].num==x){
            show(a[i]);
            break;
        }
        
return 0;
}

```
## 二、面向对象设计(C++)
```c++
#include<bits/stdc++.h>
using namespace std;
class student{

private:
    int num,b[5],score;
    string name;
public:
    student(int x,string y,int *t){
    
        num=x;
        name=y;
        score=0;
        for(int i=0; i<5; i++){
            b[i]=t[i];
            score+=b[i];
        }
    }
    friend ostream &operator <<(ostream &ct,const student &t){
    
        ct<<t.num<<' '<<t.name;
        for(int i=0; i<5; i++) ct<<' '<<t.b[i];
        ct<<' '<<t.score<<endl;
        return ct;
    }
    bool operator ==(const student &tmp){
    
        return this->num==tmp.num;
    }
    bool operator <(const student &tmp){
    
        return this->score>tmp.score;
    }
};
int main(){
    int n,x,t[5];
    string y;
    vector<student> a;
    vector<student>::iterator p;
    
    cin>>n;
    while(n--){
        cin>>x>>y;
        for(int i=0; i<5; i++) cin>>t[i];
        a.push_back(student(x,y,t));
    }
    sort(a.begin(),a.end());
    for(p=a.begin(); p!=a.end(); p++) cout<<(*p);
    
    cin>>x;
    cout<<(*find(a.begin(),a.end(),student(x,y,t)));
    
return 0;
}
```
## 三、面向对象设计(JAVA)
```java
import java.util.*;
class student{

    int num,score=0;
    int []b=new int[5];
    String name;
    public student(int x,String y,int []t){
    
        num=x;
        name=y;
        for(int i=0;i<5;i++){
            b[i]=t[i];
            score+=b[i];
        }
    }
    void show(){
    
        System.out.print(num+" "+name);
        for(int tt:b) System.out.print(" "+tt);
        System.out.println(" "+score);
    }
}
public class Main{

    public static void main(String[] args){
    
        int n,x;
        int []t=new int[5];
        String y;
        Vector<student> a=new Vector<student>();
        Iterator<student> p;
        
        Scanner input=new Scanner(System.in);
        n=input.nextInt();
        
        while(n--!=0){
            x=input.nextInt();
            y=input.next();
            for(int i=0;i<5;i++) t[i]=input.nextInt();
            a.add( new student(x,y,t));
        }
        Collections.sort(a, new Comparator<student>() {
            @Override
            public int compare(student o1, student o2) {
                return o2.score-o1.score;
            }
        });
        for(student tt:a) tt.show();
        
        x=input.nextInt();
        for(student tt:a)
            if(tt.num==x){
                tt.show();
                break;
            }
    }
}
```
