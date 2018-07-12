## 一、基本語法
* `for(Type it : ArrayName) {}`foreach遍歷

* 抽象類和接口對比

|参数|抽象类|接口|
|---|---|---|
|默认的方法实现|它可以有默认的方法实现|接口完全是抽象的，不存在方法的实现|
|实现|子类使用extends关键字来继承抽象类。如果子类不是抽象类的话，它需要提供抽象类中所有声明的方法的实现|子类使用关键字implements来实现接口。它需要提供接口中所有声明的方法的实现|
|构造器|抽象类可以有构造器|接口不能有构造器|
|与正常Java类的区别|除了你不能实例化抽象类之外，它和普通Java类没有任何区别|接口是完全不同的类型|
|访问修饰符|抽象方法可以有public、protected和default这些修饰符|接口方法默认修饰符是public。你不可以使用其它修饰符。|
|main方法|抽象方法可以有main方法并且我们可以运行它|接口没有main方法，因此我们不能运行它。|
|多继承|抽象方法可以继承一个类和实现多个接口|接口只可以继承一个或多个其它接口|
|速度|它比接口速度要快|接口是稍微有点慢的，因为它需要时间去寻找在类中实现的方法。|
|添加新方法|如果你往抽象类中添加新的方法，你可以给它提供默认的实现。因此你不需要改变你现在的代码。|如果你往接口中添加方法，那么你必须改变实现该接口的类。|

## 二、Collection

### 1. Collection (接口)
* `import java.util.Collection`導入包

### 2. ArrayList (抽象類)
* `import java.util.ArrayList`導入包 
* `ArrayList a = new ArrayList()`定義鏈表
* `ArrayList<Integer> a = new Arraylist<>()`用范型定義Integer對象鏈表

### 3. Set
### 4. List
### 5. Queue
### 6. Stack

1. `a.get(index)`獲取指定位置元素
2. `a.add(object)`末尾添加對象
3. `a.size()`鏈表長度


## 四、Map
### 1. HashMap

