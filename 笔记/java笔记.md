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

## 二、List 接口

* ArrayList: 最常用的List实现类，内部是通过数组实现的，适合随机查找和遍历，不适合插入和删除。
* LinkedList: 用链表结构存储数据，适合数据的动态插入和删除，随机访问和遍历速度比较慢。此外可以用于操作表头和表尾元素，可以当作堆栈、队列和双端队列使用。
* Vector: 通过数组实现，支持线程的同步，從而避免多线程同时写而引起的不一致性，但实现同步需要很高的花费，因此访问Vector比访问ArrayList慢。

#### 1. ArrayList (Collection, Iterable, List)
1. `import java.util.ArrayList`導入類包 
2. `import java.util.List` 導入 **List** 接口
3. `import java.util.Collection`導入 **Colletion** 接口
4. `List a = new ArrayList(ct)`定義鏈表，ct可以定長
5. `List<Integer> a = new Arraylist<>()`用范型定義Integer對象鏈表
6. `Collection`

#### 2. LinkedList (Collection, Iterable, List, Queue, Deque)
1. `import java.util.LinkedList` 導入 **LinkedList** 類包
2. `import java.util.Queue`導入 **Colletion** 接口
3. `import java.util.Deque` 導入 **List** 接口
4. `List a = new LinkedList()`定義鏈表
5. `Queue a = new LinkedList()`定義隊列
6. `Deque a = new LinkedList()`定義雙端隊列

#### 3. Vector, Stack (Collection, Iterable, List)
1. `import java.util.Vector`導入 **Vector**類包
2. `List a = new Vector()`定義Vector
3. `List a = new Stack()`定義棧
4. `Vector a = new Stack()`定義棧以Vector作爲接口

* `a.add(int, object)`在指定位置插入對象，index可省去 (1, 2, 3)
* `a.add(int, Collection<>)`尾部添加整個容器 (1, 2, 3)
* `a.clear()`清除全部對象 (1, 2, 3)
* `object a.clone()`返回淺拷貝，即引用 (1, 2, 3)
* `boolean a.contains(object)`是否存在某對象 (1, 2, 3)
* `object a.get(int)`獲取索引位置的對象 (1, 2, 3)
* `int a.indexOf(object)`第一次出現的索引，不存在則-1 (1, 2, 3)
* `int a.lastIndexOf(int)`最後一次出現的索引，不存在則-1 (1, 2, 3)
* `boolean a.isEmpty()`是否為空 (1, 2, 3)
* `object a.remove(int)`刪除指定位置對象並返回 (1, 2, 3)
* `boolean a.remove(object)`刪除對象成功則true (1, 2, 3)
* `object a.removeFirst()`刪除第一個對象並返回 (2)
* `object a.removeLast()`刪除最後對象並返回 (2)
* `a.removeRange(int, int)`索引區間全部刪除 (1, 3)
* `ListIterator<> a.ListIterator()`獲取迭代器 (1, 3)
* `ListIterator<> a.ListIterator(int)`從索引處獲取迭代器 (1, 2, 3)
* `a.set(int, object)`修改對象 (1, 2, 3)
* `a.size()`對象數量 (1, 2, 3)
* `List<> a.subList(int, int)`返回區間子鏈表 (1, 3)
* `object[] a.toArray()`返回對象數組 (1, 2, 3)
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
* `object a.peek() / peekFirst()`獲取隊首/棧頂，空則null (2)
* `object a.peekLast()`獲取隊尾，空則null (2)
* `object a.poll() / pollFirst()`移除隊首對象並返回 (2)
* `object a.pollLast()`移除隊尾對象並返回 (2)
* `object a.pop()`出棧 (2, 3)
* `a.push(object)`入棧 (2, 3)
× `a.setSize()`重新設置Vector大小 (3)
* `a.toString()`返回Vector構成的數組 (3)
* `a.empty()`判斷是否棧空 (3)

## 三、Set 接口

* HashSet: 通過哈希表實現的有序集合，其對象并没有以某种特定顺序来存放。
* TreeSet: 通過樹形結構實現的有序集合，其對象以升序顺序存储，访问和遍历的时间很快。
* LinkedHashSet: 以元素插入的顺序来维护集合的链接表，以插入的顺序在集合中迭代；  

#### 1. HashSet (Collection, Iterable, Set)
1. `import java.util.HashSet`導入包
2. `import java.util.Set`導入 **Set** 接口
3. `Set a = new HashSet()`定義集合，哈希表實現

#### 2. TreeSet (Collection, Iterable, SortedSet, Set)
1. `import java.util.TreeSet`導入包
2. `import java.util.SortedSet`導入 **SortedSet** 接口
3. `Set a = new TreeSet()`定義集合，樹形結構實現
4. `Sorted a = new TreeSet()`以SortedSet接口定義集合

#### 3. LinkedHashSet(Collection, Iterable, HashSet, Set)
1. `import java.util.LinkedHashSet`導入包
2. `Set a = new LinkedHashSet`定義無序集合
3. `HashSet a = new LinkedHashSet`定義無序集合以HashSet作爲接口

* `boolean a.add(object)`添加對象，若已存在則false (1, 2, 3)
* `a.clear()`清空集合 (1, 2, 3)
* `object a.clone()`返回集合的淺拷貝 (1, 2, 3)
* `boolean a.contains(object)`判斷是否存在某對象 (1, 2, 3)
* `boolean a.isEmpty()`判斷集合是否爲空 (1, 2, 3)
* `boolean a.remove(object)`刪除某對象，不存在則false (1, 2, 3)
* `int a.size()`集合的大小 (1, 2, 3)
* `boolean a.addAll(Collection<>)`添加容器內所有對象 (2, 3)
* `Comparator<super object> a.comparator()`返回集合元素排序的比較器，自然排序則null (2)
* `Iterator<> a.iterator()`返回正向迭代器 (1, 2, 3)
* `Iterator<> a.descendingIterator()`返回反向迭代器 (1, 2, 3)
* `object a.first()`返回最小對象 (2)
* `object a.last()`返回最大對象 (2)
* `object a.floor(object)`返回小於等於某對象的最大對象 (2)
* `object a.ceiling(object)`返回大於等於某對象的最小對象 (2)
* `object a.lower(object)`返回小於某對象的最大對象 (2)
* `object a.higher(object)`返回大於某對象的最小對象 (2)
* `object a.pollFirst()`移除最小對象並返回 (2)
* `object a.pollLast()`移除最大對象並返回 (2)
* `SortedSet<> a.subSet(object, object)`返回左閉右開區間內對象集合的引用 (2)
* `SortedSet<> a.headSet(object)`返回小於某對象的對象集合引用 (2)
* `SortedSet<> a.tailSet(object)`返回大於等於某對象的對象集合引用 (2)
* `String a.toString()` 轉換爲字符串 (1, 2, 3)
* `object[] a.toArray()` 轉換爲對象數組 (1, 2, 3)
* `boolean a.equals()`判斷兩集合是否相等 (1, 2, 3)

## 四、Map 接口

#### 1. HashMap (Map)
* `import java.util.Map`


#### 2. TreeMap, HashTable, LinkedHashMap 

## 五、Collections 靜態容器方法

* Collections提供很多對容器 (Collection) 進行操作的靜態方法，常用容器接口 (Collection Interface) 有List, Set, Map, Queue, Deque。
* `import java.util.Collections` 導入包

* `Queue Collections.asLifoQueue(Deque)`雙端隊列轉換爲隊列
* `boolean Collections.disjoint(Collection, Collection)`容器無交集則true，否則false
* `Collections.fill(List, object)`全部改成某對象
* `int Collections.frequency(Collection, object)`返回對象出現的次數
* `Collections.copy(List, List)`後者全部拷貝到前者中
* `int Collections.indexOfSubList(List, List)`返回後者在前者中第一次出現的索引，不存在則-1
* `int Collections.lastIndexOfSubList(List, List)`返回後者在前者中最後出現的索引，不存在則-1
* `object Collections.max(Collection, Comparator)`返回容器中最大值，比較器可省去
* `object Collections.min(Collection, Comparator)`返回容器中最小值，比較器可省去
* `List Collections.nCopies(int, object)`返回n個對象構成的List
* `Collections.reverse(List)`顛倒順序
* `Comparator Collections.reverseOrder()`返回逆序比較器
* `Comparator Collections.reverseOrder(Comparator)`返回某比較器的逆序比較器
* `int Collections.binarySearch(List, object)`在有序List中二分查找索引，不存在則返回負數(-index - 1)，index爲該對象應該插入的位置
* `int Collections.binarySearch(List, object, Comparator)`以特定比較器二分查找，同上
* `boolean Collections.replaceAll(List, object, object)`List替換對象，不存在則false
* `Collections.sort(List, Comparator)`容器進行升序，比較器可省去
* `Collections.swap(List, int, int)`交換指定位置處的對象
* ``
* ``
* ``
* ``
* ``





備忘：
Scanner
BigInteger
BigDecimal
Collections.Sort() & Comparator
Iterator
String
Character
