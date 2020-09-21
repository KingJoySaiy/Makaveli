## 一、基本語法
* `java.lang.*`默認包自動導入
* `for(Type it : ArrayName) {}`foreach遍歷
* `@override`出現在方法前表示重寫，常用在子類中從而覆蓋父類方法
* 基本類型之間用`==`按值比較，對象類型之間用`a.equal(b)`按引用比較

1.  對象類型與基本類型:
 
|對象類|基本類|對象類|基本類|
|---|---|---|---|
|Integer|int|Short|short|
|Double|double|Float|float|
|Long|long|Byte|byte|
|Boolean|boolean|Character|char|
|String|-|||

2. 抽象類和接口對比

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

### 1. ArrayList (Collection, Iterable, List)
1. `import java.util.ArrayList`導入類包 
2. `import java.util.List` 導入 **List** 接口
3. `import java.util.Collection`導入 **Colletion** 接口
4. `List a = new ArrayList(ct)`定義鏈表，ct可以定長
5. `List<Integer> a = new Arraylist<>()`用范型定義Integer對象鏈表
6. `Collection`

### 2. LinkedList (Collection, Iterable, List, Queue, Deque)
1. `import java.util.LinkedList` 導入 **LinkedList** 類包
2. `import java.util.Queue`導入 **Colletion** 接口
3. `import java.util.Deque` 導入 **List** 接口
4. `List a = new LinkedList()`定義鏈表
5. `Queue a = new LinkedList()`定義隊列
6. `Deque a = new LinkedList()`定義雙端隊列

### 3. Vector, Stack (Collection, Iterable, List)
1. `import java.util.Vector`導入 **Vector**類包
2. `List a = new Vector()`定義Vector
3. `List a = new Stack()`定義棧
4. `Vector a = new Stack()`以父類Vector定義棧

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

### 1. HashSet (Collection, Iterable, Set)
1. `import java.util.HashSet`導入包
2. `import java.util.Set`導入 **Set** 接口
3. `Set a = new HashSet()`定義集合，哈希表實現

### 2. TreeSet (Collection, Iterable, SortedSet, Set)
1. `import java.util.TreeSet`導入包
2. `import java.util.SortedSet`導入 **SortedSet** 接口
3. `Set a = new TreeSet()`定義集合，樹形結構實現
4. `Sorted a = new TreeSet()`以SortedSet接口定義集合

### 3. LinkedHashSet(Collection, Iterable, HashSet, Set)
1. `import java.util.LinkedHashSet`導入包
2. `Set a = new LinkedHashSet`定義無序集合
3. `HashSet a = new LinkedHashSet`以父類HashSet定義無序集合

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

* HashMap: 最常用的Map，用散列表存儲鍵值對，能夠快速隨機訪問數據。只允許一條記錄鍵爲null，不支持線程同步。
* TreeMap: 用樹形結構有序存儲鍵值對，實現了SortedMap接口。默認按鍵升序排序，也可以指定比較器。
* LinkedHashMap: 按插入順序進行存儲，是無序哈希表。

### 1. HashMap (Map)
1. `import java.util.HashMap`導入包
2. `import java.util.Map`導入 **Map** 接口
3. `Map<Key, Value> a = new HashMap<>()`定义存储键值对的哈希表

### 2. TreeMap (Map, SortedMap)
1. `import java.util.TreeMap`導入包
2. `import java.util.SortedMap`導入 **SortedMap** 接口
3. `Map<Key, Value> a = new TreeMap<>()`定義TreeMap
4. `SortedMap<key, value> a = new TreeMap()`以SortedMap爲接口定義TreeMap

### 3. LinkedHashMap (Map, HashMap)
1. `import java.util.LinkedHashMap`導入包
2. `Map<Key, Value> a = new LinkedHashMap<>()`定義LinkedHashMap
3. `HashMap<Key, Value> a = new LinkedHashMap<>()`以父類HashMap定義LinkedHashMap

* `Map.Entry<Key, Value>`内部泛型接口类型 (1, 2)
* `Map.Entry(key, value)`内部泛型接口对象 (1, 2)
* `a.clear()`清空所有对象 (1, 2, 3)
* `Map a.clone()`返回哈希表浅拷贝 (1, 2, 3)
* `Value a.get(Key)`按照key获取value，不存在则null (1, 2, 3)
* `boolean a.isEmpty()`判断哈希表是否为空 (1, 2, 3)
* `boolean a.containsKey(key)`判断是否存在某键 (1, 2, 3)
* `boolean a.containsValue(value)`判断是否存在某值 (1, 2, 3)
* `Set<Map.Entry<Key, Value>> a.entrySet()`获取内部键值集合 (1, 2, 3)
* `Set<Key> a.keySet()`获取键集合 (1, 2, 3)
* `Value a.put(Key, Value)`添加键值对，返回键之前的值 (1, 2, 3)
* `a.putAll(b)`添加整个map (1, 2, 3)
* `Value a.remove(Key)`删除键值对，返回值 (1, 2, 3)
* `int a.size()`返回键值对个数 (1, 2, 3)
* `Collection<Value> a.values()`返回值构成的容器 (1, 2, 3)
* `int a.hashCode()`返回哈希码 (1, 2, 3)
* `String a.toString()`返回字符串表述 (1, 2, 3)
* `boolean a.equals(object)`判断对象是否相等 (1, 2, 3)
* `Comparator<super Key> a.comparator()`返回哈希表的比較器，自然序則null (2)
* `Map.Entry<Key, Value> a.firstEntry()`返回鍵最小的鍵值對，表空則null (2)
* `Map.Entry<Key, Value> a.lastEntry()`返回鍵最大的鍵值對，表空則null (2)
* `Map.Entry<Key, Value> a.floorEntry(Key)`返回鍵小於等於key的最大的鍵值對，表空則null (2)
* `Map.Entry<Key, Value> a.ceilingEntry(Key)`返回鍵大於等於key的最小的鍵值對，不存在則null (2)
* `Map.Entry<Key, Value> a.lowerEntry(Key)`返回鍵小於key的最大鍵值對，表空則null (2)
* `Map.Entry<Key, Value> a.higherEntry(Key)`返回鍵大於key的最小鍵值對，表空則null (2)
* `Key a.firstKey()`返回最小的鍵，表空則null (2)
* `Key a.lastKey()`返回最大的鍵，表空則null (2)
* `Key a.floorKey(Key)`返回小於等於key的最大key，表空則null (2)
* `Key a.ceilingKey(Key)`返回鍵大於等於key的最小的鍵，不存在則null (2)
* `Key a.lowerKey(Key)`返回小於key的最大key，表空則null (2)
* `Key a.higherKey(Key)`返回大於key的最小key，表空則null (2)
* `Map.Entry<Key, Value> a.pollFirstEntry()`刪除第一個鍵值對並返回 (2)
* `Map.Entry<Key, Value> a.pollLastEntry()`刪除最後一個鍵值對並返回 (2)
* `SortedMap<Key, Value> a.headMap(Key)`返回小於等於key的子哈希表引用 (2)
* `SortedMap<Key, Value> a.tailMap(Key)`返回大於key的子哈希表引用 (2)
* `SortedMap<Key, Value> a.subMap(Key, Key)`返回key左閉右開區間的子哈希表引用 (2)

## 五、Queue、Deque接口
* Queue接口与List, Set一样继承自Collection接口，支持队列的常见操作。常用的实现类有LinkedList和PriorityQueue。
* Deque是Queue的子接口，用于实现双端队列，同时也能实现栈。

### 1. PriorityQueue(Queue)
1. `import java.util.Queue`导入 **Queue** 接口
2. `import java.util.PriorityQueue`导入包
3. `Queue<Integer> a = new PriorityQueue<>()`定义优先队列（默认最小堆）
4. 利用Comparable对象创建优先队列排序规则，如下：
```java
Queue<MyClass> a = new PriorityQueue<>(new Comparator<MyClass>(){
    @Override
    public int compare(Myclass o1, MyClass o2) {
        return o1 - o2;
    }
});
```

### 2. ArrayDeque(Queue, Deque)
1. `import java.util.ArrayQueue`导入包
2. `Deque<Integer> a = new ArrayQueue<>()`定义双端队列

### 3. LinkerList(List, Queue, Deque)
（二、List接口）

* `boolean a.offer(object)`入队操作，返回是否成功(1, 2, 3)
* `object a.poll()`出队并返回(1, 2, 3)
* `object a.peek()`获取队首(1, 2, 3)
* `boolean a.contains(object)`队列中是否有某元素(1, 2, 3)
* `void a.clear()`清空队列(1, 2, 3)
* `boolean a.equals(objeact)`判断两队列是否对象数值相等(1, 2, 3)
* `boolean a.isEmpty()`判断队列是否为空(1, 2, 3)
* `int a.size()`返回队列大小(1, 2, 3)
* `boolean a.remove(object)`按值删除对象(1, 2, 3)
* `object[] a.toArray()`返回对象数组(1, 2, 3)
* `void a.offerFirst(object)`在队首位置添加对象(2, 3)
* `void a.offerLast(object)`在队尾位置添加(2, 3)
* `object a.peekFirst()`获取队首(2, 3)
* `object a.peekLast()`获取队尾(2, 3)
* `object a.pollFirst()`弹出队首(2, 3)
* `object a.pollLast()`弹出队尾(2, 3)
* `object a.pop()`出栈/弹出队尾(2, 3)
* `void a.push(object)`入栈/添加队尾(2, 3)

## 六、Collections 靜態容器方法

1. **Collections** 提供很多對容器 (Collection) 進行操作的靜態方法，常用容器接口 (Collection Interface) 有List, Set, Map, Queue, Deque。
2. `import java.util.Collections` 導入包

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

## 七、常用基本類

### 1. Character 基本字符類

1. **Character** 是基本類型 **char** 的封裝類，用於對單個字符進行操作
2. `import java.lang.Character`導入包，也可不加會自動導入
3. `Character a = new Character('c') / 'c'`定義字符對象

* `char a.charValue()`返回基本類型
* `String a.toString()`返回字符串對象
* `int a.compareTo(Character)`返回字典序差值
* `boolean a.equals(Character)`比較兩字符
* `Character Character.valueOf(char)`基本類型轉對象類型
* `boolean Character.isAlphabetic() / isLetter`判斷是否是拉丁字母
* `boolean Character.isDigit()`判斷是否是數字
* `boolean Character.isLowerCase()`判斷是否小寫字母
* `boolean Character.isUpperCase()`判斷是否大寫字母
* `boolean Character.isLetterOrDigit()`判斷是否是字母或數字
* `String Character.toString(Char)`返回字符串對象
* `boolean Character.toTitleCase(char)`首字母大寫
* `boolean Character.toLowerCase(char)`大寫轉小寫
* `boolean Character.toUpperCase(char)`小寫轉大寫

### 2. Integer 基本整數類

1. **Integer** 是基本類型 **int** 的封裝類，用於對整數的基本操作
2. `import java.lang.Integer`導入包，也可不加會自動導入
3. `Integer a = new Integer(1) / 1`定義整數對象

* `boolean a.equals(Integer)`比較兩個對象是否相等
* `double a.doubleValue()`返回double數值
* `int a.intValue()`返回int數值
* `long a.longValue()`返回long數值
* `short a.shortValue()`返回short數值
* `String a.toString()`整型轉爲字符串
* `int Integer.praseInt(String)`字符串轉爲整型
* `int Integer.bitCount(a)`返回二進制數中1的個數
* `String Integer.toBinaryString(int)`int轉爲二進制字符串
* `String Integer.toString(int)`整型轉爲字符串

### 3. String 字符串相關

* String：不可變字符串對象，每次修改都要生成新對象並改變引用，速度較慢。
* StringBuffer：線程安全的可變字符序列，可在必要時對一些方法進行同步，在實例上的操作順序與每個線程的方法調用順序一致。
* StringBuilder：不支持多線程的可變字符序列，比String和StringBuffer快很多，因此被單線程使用時優先採用該類。

#### 1. String 字符類

1. `import java.lang.String`導入包，也可不加會自動導入
2. `String a = new String()`定義字符串對象

#### 2. StringBuffer 字符串緩衝

1. `import java.lang.StringBuffer`導入包，也可不加會自動導入
2. `StringBuffer a = new StringBuffer()`定義StringBuffer對象

#### 3. StringBuilder 字符串構建

1. `import java.lang.StringBuilder`導入包，也可不加會自動導入
2. `StringBuffer a = new StringBuilder()`定義StringBuffer對象

* `char a.charAt(int)`返回指定位置處的字符 (1, 2, 3)
* `int a.compareTo(String)`返回第一個不同字符的字典序差值 (1)
* `String a.concat(String)`字符串串聯到最後 (1)
* `boolean a.contains(String)`判斷是否是子串 (1)
* `boolean a.equals(String)`判斷字符串是否相等 (1, 2, 3)
* `int a.indexOf(char / String)`返回子串第一次出現的索引，不存在則-1 (1, 2, 3)
* `int a.lastIndexOf(char / String)`返回子串最後一次出現的索引，不存在則-1 (1, 2, 3)
* `boolean a.isEmpty()`判斷是否是空串 (1)
* `int a.length()`返回串長 (1, 2, 3)
* `String a.replace(char, char)`替換字符 (1)
* `String a.replace(String, String)`替換字符串 (1)
* `String a.replaceFirst(String, String)`替換第一個匹配的字符串 (1)
* `Object a.replace(int, int, String)`替換區間內所有字符 (2, 3)
* `String[] a.split(String)`分割字符串 (1)
* `String a.subString(int, int)`返回子串，省去二參數則到串尾 (1)
* `char[] a.toCharArray()`轉換爲字符數組 (1)
* `String a.toLowerCase()`大寫轉小寫 (1)
* `String a.toUpperCase()`小寫轉大寫 (1)
* `String a.clone`返回淺拷貝 (1)
* `String String.valueOf(char[] / double / float/ int)`轉換爲字符串 (1)
* `String String.valueOf(boolean / char / long)`轉換爲字符串 (1)
* `Object a.append(boolean / char / char[] / double / float / int / String)`末尾添加字符 (2, 3)
* `int a.capacity()`返回當前容量 (2, 3)
* `int a.codePointAt()`返回指定索引處的字符ASCII碼 (2, 3)
* `int a.codePointBefore()`返回索引之前的字符ASCII碼 (2, 3)
* `Object a.delete(int, int)`刪除區間內所有字符 (2, 3)
* `object a.deleteCharAt(int)`刪除某位置字符 (2, 3)
* `Object a.insert(int, boolean / char / char[] / double / float / int / String)`指定位置插入字符 (2, 3)
* `Object a.reverse()`逆序字符串 (2, 3)
* `void a.setCharAt(int, char)`改變某位置字符 (2, 3)
* `String a.substring(int, int)`獲取子串新對象 (2, 3)
* `String a.toString()`轉爲字符串 (2, 3)

### 4. Scanner 讀入類
1. `import java.util.Scanner`導入包
2. `Scanner in = new Scanner(Systen.in / new File("...") / String)`定義讀入類

* `a.close()`關閉讀入
* `boolean a.hasNext()`判斷是否還能讀入
* `boolean a.hasNextBigDecimal()`判斷下一讀入能否作爲BigDecimal
* `boolean a.hasNextBigInteger()`判斷下一讀入能否作爲BigInteger
* `a.hasNextBoolean / Double / Float / Int / Long / Short / Byte ()`判斷能否繼續讀取基本類型
* `boolean a.hasNextLine()`判斷能否再讀取一行
* `String a.next()`返回下一個整串
* `BigDecimal a.nextBigDecimal()`返回下一個大十進制數
* `BigInteger a.nextBigInteger()`返回下一個大整數
* `Object a.nextBoolean / Double / Float / Int / Long / Short / Byte ()`返回下一個基本類型
* `String a.nextLine()`返回下一行
* `String a.toString()`轉爲字符串
* `boolean a.equals(object)`判斷是否相等

## 八、大數類

* BigInteger：提供對較大的整數的基本操作
* BigDecimal：類提供對較大的十進制數（包括小數）的基本操作

### 1. BigInteger

1. `import java.math.BigInteger`導入包
2. `BigInteger a = new BigInteger(String)`定義大整數對象，字符串必須只包含數字

### 2. BigDecimal

1. `import java.math.BigDecimal`導入包
2. `BigDecimal a = new BigDecimal(int / long / char[] / String / double / BigInteger)`定義大十進制數

* `Object a.abs()`返回絕對值 (1, 2)
* `boolean a.equals(object)`判斷是否相等 (1, 2)
* `Object a.add(Object)`加法 (1, 2)
* `Object a.subtract(Object)`減法 (1, 2)
* `Object a.multiply(Object)`乘法 (1, 2)
* `Object a.divide(Object)`除法 (1, 2)
* `Object a.remainder(Object)`取模運算 (1, 2)
* `Object[] a.divideAndRemainder(Object)`返回商和餘數2個值 (1, 2)
* `Object a.max(Object)`返回較大值 (1, 2)
* `Object a.min(Object)`返回較小值 (1, 2)
* `Object a.mod(Object)`取模運算 (1)
* `Object a.negate()`返回相反數 (1, 2)
* `Object a.and(Object)`按位與 (1)
* `Object a.andNot(Object)`按位與非 (1)
* `Object a.not()`按位取反 (1)
* `Object a.or(Object)`按位或 (1)
* `Object a.xor(Object)`按位抑或 (1)
* `int a.bitCount()`返回二進制數中1的個數 (1)
* `int a.compareTo(Object)`比較大小，返回差值 (1, 2)
* `double a.doubleValue()`轉換爲雙精度浮點數 (1, 2)
* `float a.floatValue()`轉換爲單精度浮點數 (1, 2)
* `int a.intValue()`轉換爲整型 (1, 2)
* `long a.longValue()`轉換爲長整型 (1, 2)
* `Object a.gcd(Object)`返回兩數絕對值的最大公約數gcd (1)
* `boolean a.isProbablePrime()`判斷是否是素數 (1)
* `Object a.nextProbablePrime()`返回下一個素數 (1)
* `Object a.pow(int)`返回this^x (1, 2)
* `Object a.shiftLeft(int)`左移若干位 (1)
* `Object a.shiftRight(int)`右移若干位 (1)
* `String a.toString()`大整數轉字符串 (1, 2)
* `Object Object.valueOf(long)`長整型轉大整數 (1, 2)
* `Object a.clone()`返回淺拷貝 (1)
* `Object a.divideToIntegralValue()`向下取整 (2)
* `Object a.movePointLeft()`小數點左移一位 (2)
* `Object a.movePointRight()`小數點右移一位 (2)
* `int a.precision()`返回精度 (2)

## 九、Comparable / Comparator 接口

* Comparable接口一般由子類通過implements關鍵字實現，直接修改實體類的比較方式，繼而在比較或排序時不需要傳入比較器參數。
* Comparator接口提供重寫容器的排序方法與分組方式，無需實現Comparable接口，無需改變實體類的內容，只需新建比較器對象作爲方法參數傳入即可。

1. `import java.util.Comparator`导入包
2. Comparable接口的實現如下，通過重寫compareTo方法而修改實體類的比較方式。

```java
class object implements Comparable<object> {
    public int value;
    @Override
    public int compareTo(object t) {
        return value - t.value;
    }
}
```

3. Comparator比較器對象定義如下，修改compare方法即可，可以在`Collections.sort`或`Arrays.sort`中作爲參數使用。

```java
    Comparator<object> comparator = new Comparator<>() {
        @Override
        public int compare(object o1, object o2) {
            return o1.value - o2.value;
        }
    };
    Collections.sort(objects, comparator);
```

4. 其中`compareTo`和`compare`方法返回值都是int，若爲負數則左對象在右對象前，爲0則兩視爲對象相等，正數同理。

## 十、 Math 數學相關方法

* `java.lang.Math`包會自動導入，提供了基本的數學相關的靜態方法，處理的類型有`double, float, int, long, short`。

* `num Math.abs(x)`返回絕對值
* `num Math.acos(x)`返回反餘弦值
* `num Math.asin(x)`返回反正弦值
* `num Math.atan(x)`返回反正切值
* `num Math.atan2(x, y)`向量與x軸正方向的相對夾角，範圍(-pi ~ pi)
* `num Math.cos(x)`返回餘弦值
* `num Math.cosh(x)`返回雙曲餘弦值`cosh(x) = (e^x + e^(-x)) / 2`
* `num Math.sin(x)`返回正弦值
* `num Math.sinh(x)`返回雙曲正弦值`sinh(x) = (e^x - e^(-x)) / 2`
* `num Math.tan(x)`返回正切值
* `num Math.tanh(x)`返回雙曲正切值`tanh(x) = sinh(x) / cosh(x) = (e^x - e^(-x)) / (e^x + e^(-x))`
* `num Math.addExact(x, y)`返回兩數之和
* `num Math.exp(x)`返回歐拉數的x次冪`e^x`
* `num Math.ceil(x)`向上取整
* `num Math.floor(x)`向下取整
* `num Math.floorDiv(x, y)`返回 x/y 向下取整
* `num Math.floorMod(x, y)`返回 x%y 向下取整
* `num Math.hypot(x, y)`返回點到原點的距離`sqrt(x^2 + y^2)`
* `num Math.log(x)`返回以歐拉數e爲底的對數
* `num Math.log10(x)`返回以10爲底的對數
* `num Math.max(x, y)`返回較大值
* `num Math.min(x, y)`返回較小值
* `num Math.multiplyExact(x, y)`返回兩數的乘積，溢出則拋出異常
* `num Math.negateExact(x)`返回相反數
* `num Math.pow(x, y)`返回`x ^ y`
* `num Math.random()`返回[0, 1)之間的隨機數
* `num Math.round(x)`四捨五入
* `num Math.signum(x)`處理浮點誤差，0返回0，正數返回1，負數返回-1
* `num Math.sqrt(x)`開根號

備忘：

Iterator

Pair<object, object>

正則表達式

lambda表達式

Swing : JFrame / JTable
