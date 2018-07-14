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

## 二、List接口相關

* ArrayList是最常用的List实现类，内部是通过数组实现的，适合随机查找和遍历，不适合插入和删除。
* LinkedList是用链表结构存储数据的，很适合数据的动态插入和删除，随机访问和遍历速度比较慢。此外可以用于操作表头和表尾元素，可以当作堆栈、队列和双端队列使用。
* Vector也是通过数组实现的，不同的是它支持线程的同步，避免多线程同时写而引起的不一致性，但实现同步需要很高的花费，因此访问Vector比访问ArrayList慢。

#### 1. ArrayList (Collection, List)
1. `import java.util.ArrayList`導入類包 
2. `import java.util.List` 導入 **List** 接口
3. `import java.util.Collection`導入 **Colletion** 接口
4. `List a = new ArrayList(ct)`定義鏈表，ct可以定長
5. `List<Integer> a = new Arraylist<>()`用范型定義Integer對象鏈表

#### 2. LinkedList (Collection, List, Queue, Deque)
1. `import java.util.LinkedList` 導入 **LinkedList** 類包
2. `import java.util.Queue`導入 **Colletion** 接口
3. `import java.util.Deque` 導入 **List** 接口
4. `List a = new LinkedList()`定義鏈表
5. `Queue a = new LinkedList()`定義隊列
6. `Deque a = new LinkedList()`定義雙端隊列

#### 3. Vector (Collection, List)


* `a.add(int, object)`在指定位置插入對象，index可省去 (1, 2)
* `a.clear()`清除全部對象 (1, 2)
* `object a.clone()`返回淺拷貝，即引用 (1, 2)
* `boolean a.contains(object)`是否存在某對象 (1, 2)
* `object a.get(int)`獲取索引位置的對象 (1, 2)
* `int a.indexOf(object)`第一次出現的索引，不存在則-1 (1, 2)
* `int a.lastIndexOf(int)`最後一次出現的索引，不存在則-1 (1, 2)
* `boolean a.isEmpty()`是否為空 (1)
* `object a.remove(int)`刪除指定位置對象並返回 (1, 2)
* `boolean a.remove(object)`刪除對象成功則true (1, 2)
* `object a.removeFirst()`刪除第一個對象並返回 (2)
* `object a.removeLast()`刪除最後對象並返回 (2)
* `a.removeRange(int, int)`索引區間全部刪除 (1)
* `ListIterator<> a.ListIterator()`獲取迭代器 (1)
* `ListIterator<> a.ListIterator(int)`從索引處獲取迭代器 (1, 2)
* `a.set(int, object)`修改對象 (1, 2)
* `a.size()`對象數量 (1)
* `List<> a.subList(int, int)`返回區間子鏈表 (1)
* `object[] a.toArray()`返回對象數組 (1, 2)
* `boolean it.hasNext()`判斷迭代器有無後一個 (1)
* `boolean it.hasPrevious()`判斷迭代其有無前一個 (1)
* `object it.next()`下一個迭代器引用 (1)
* `object it.previous()`前一個迭代其引用 (1)
* `object a.getFirst()`獲取首對象 (2)
* `object a.getLast()`獲取尾對象 (2)
* `a.addFirst(object)`鏈尾添加對象 (2)
* `a.addLast(object)`鏈首添加對象 (2)
* `boolean a.offer() / offerLast`隊尾添加對象 (2)
* `boolean a.offerFirst()`隊首添加對象 (2)
* `object a.peek() / peekFirst()`獲取隊首，空則null (2)
* `object a.peekLast()`獲取隊尾，空則null (2)
* `object a.poll() / pollFirst()`移除隊首對象並返回 (2)
* `object a.pollLast()`移除隊尾對象並返回(2)
* `object a.pop()`出棧 (2)
* `a.push(object)`入棧 (2)

## 三、Set接口相關

#### 3. HashSet, TreeSet (Collection, Set)
1. `import java.util.HashSet`導入包
2. `import java.util.Set`導入 **Set** 接口
3. `Set a = new HashSet()`
4. `Set<Integer> a = new HashSet<>()`

#### 4. HashMap, TreeMap, HashTable, LinkedHashMap (Map)

#### 5. Stack



* ``
* ``
* ``
* ``
* ``
* ``
* ``

