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

#### 1. ArrayList, LinkList
* `import java.util.ArrayList`導入包 
* `import java.util.List` 可用 **List** 接口
* `List a = new ArrayList(ct)`定義鏈表，ct可以定長
* `List<Integer> a = new Arraylist<>()`用范型定義Integer對象鏈表
* `ListIterator<> a.ListIterator()`返回迭代器

#### 2. HashSet, TreeSet
* `import java.util.HashSet`導入包 
* `import java.util.Set` 可用 **Set** 接口
* `Set a = new HashSet()`
* `Set<Integer> a = new HashSet<>()`

#### 3. HashMap, TreeMap, HashTable, LinkedHashMap

#### 5. Stack

#### 4. Queue (接口)


* `a.add(int, object)`在指定位置插入對象，index可省去（1）
* `a.clear()`清除全部對象（1）
* `object a.clone()`返回淺拷貝，即引用（1）
* `boolean a.contains(object)`是否存在某對象（1）
* `object a.get(int)`獲取索引位置的對象（1）
* `int a.indexOf(object)`第一次出現的索引，不存在則-1（1）
* `int a.lastIndexOf(int)`最後一次出現的索引，不存在則-1（1）
* `boolean a.isEmpty()`是否為空（1）
* `object a.remove(int)`刪除指定位置對象並返回（1）
* `boolean a.remove(object)`刪除對象成功則true（1）
* `a.removeRange(int, int)`索引區間全部刪除（1）
* `a.set(int, object)`修改對象（1）
* `a.size()`對象數量（1）
* `List<> a.subList(int, int)`返回區間子鏈表（1）
* `object[] a.toArray()`返回對象數組（1）
* `boolean it.hasNext()`判斷迭代器有無後一個（1）
* `boolean it.hasPrevious()`判斷迭代其有無前一個（1）
* `object it.next()`下一個迭代器引用（1）
* `object it.previous()`前一個迭代其引用（1）

