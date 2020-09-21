## 写在前面
* `list(map(int, input().split()))`常用于读取一行以空格分割的列表；
* 常用`assert ...`以确保某处结果是否符合预期

## 一、操作符 & 关键字

### 1.1 常见操作符

|operator               |      |
|---|---|
|a ** b                  | a的b次方|
|pow(a,b)                | a的b次方|
| a / b 			     | 算数除法，得到浮点数|
|a // b                  | 除法并向下取整|
|a + b                   | 算术加,str,list,tuple中为拼接|
|a - b                   | 算术减,set中为差集|
|a丨b                    | 逻辑或,set中为并集|
|a & b                   | 逻辑与,set中为交集|
|a ^ b                   | 逻辑异或,set中为对称差|
|x<<n / x>>n             | 左移/右移|
|~x                      | 按位取反|
|a=b					 | 赋值|
|a,b = x,y               | 对应赋值a=x,b=y|
|a += b / a -= b	     | 加法赋值/减法赋值|
|a *= b / a /= b	     | 乘法赋值/除法赋值|
|a %= b	  				  | 取模赋值|
|a**=b                   | 幂赋值a=a**b|
|a//=b                   | 整除法赋值a=a//b|
|and / or / not          | 与或非|
|a < b / a <= b          | 小于/小于等于|
|a > b / a >= b          | 大于/大于等于|
|a == b / a != b         | 等于/不等于|
|a (not) is b            | 判断标识符是否引用同一个对象|
|a < b >= c == d         | 允许链式比较|
|*a						  | 解包sequence|

### 1.1 常见关键字

|keyword| |
|---|---|
|a is (not) b            | 判断是否引用同一个对象|
|a (not) in b            | 判断a是否是b中的元素|
|pass                    | 跳过不执行操作|
|def 函数名(参数列表)      | 定义函数|
|global a                | 声明a是全局变量，作用域为全局 |
|nonlocal a|声明a不是局部变量，也不是全局变量，而是外部嵌套函数内的变量|
|sep=' '                 | 控制分隔符，默认空格|
|end='\n'                | 控制结束符，默认换行|
|with open('233.txt') as file_object:  | 打开文件并定义文件对象名为file_object|
|form time import *      | 导入模块中的函数或变量名称|
|import math as x        | 导入模块并重命名|
|del a / a[0] / a[2:5]   | 删除实体/元素/切片 |

## 二、方法

### 2.1 常用库

|import导入| |
|---|---|
|keywords                | 提供标准库关键字|
|math                    | 提供数学库|
|platform                | 获得操作系统,系统架构,python信息等|
|time                    | 获取当前时间|
|builtins                | 内建名称空间(提供不用导入就能调用的内建函数)|
|collections             | 容器库|
|unittest                | 提供代码测试工具,测试函数是否在各种情形下的行为都符合要求|

### 2.2 常用方法

|method||
|---|---|
|keywords.kwlist         | 输出标准库的所有关键字|
|type(a)                 | 返回变量a的对象类型|
|len(a)                  | 返回元素个数|
|sorted(a,reverse=True)  | 默认升序排序|
|input(x)                | 输出x，并读取下一个字符串|
|id(a)                   | 返回a的地址|
|dir(list)               | 查询类的所有属性，查询模块定义的所有名字|
|help(list)              | 查询说明文档|
|range(6)                | 范围[0,6)的整数|
|range(1,10,3)           | 范围[1,10)内间隔为3的整数|
|list(range(4))          | 将[0,4)转化为列表|
|int(a)                  | 强制转换为int|
|float(a)                | 强制转换为float|
|abs(a)                  | 取绝对值|
|pow(a, b)               | a的y次幂，同a**b|
|complex(i,j)            | 返回实虚部分别为i,j的复数|
|a.conjugate()           | 返回复数a的共轭复数|
|divmod(x,y)             | 返回数值对(x//y,x%y),结果和余数|
| isinstance(a, className) | 判断对象a是否是className或其派生类的实例 |
| issubclass(className1, className2) | 判断class1是否是class2的派生类 |

## 三、基本类型

* 字符串、列表、元组、集合可用*进行解包；字典用**解包且只能在函数中取出，无法直接使用
* 列表、集合、字典分别用[..for...]、{...for...}、{...:...for...}推导式；生成器用(...for...)推导式，可以遍历读每个迭代器；没有字典推导式；字符串推导式可以将字符列表用join转化 **''.join([c+c for c in 'abc'])**

### 3.1 字符串

|a = '233' / "233" | 单引号双引号皆可|
|---|---|
|a.upper()               | 转为大写|
|a.lower()               | 转为小写|
|a.title()               | 所有单词以大写开始，其余小写|
|a.rjust(len,char)       | 长度扩展为len,原字符在右侧，其余填充char(默认空格)|
|a.ljust(len,char)       | 同上，原字符在左侧|
|a='{0:<6d},{1:^5s}，{2:2f}'.format(23,'ab',11.2) | 字符串格式化，id省略则按原顺序(居左<,居中^,居右>，默认>)|

### 3.2 列表

|a = [1,2,3]||
|---|---|
|a.append(4)             | 末尾添上4|
|a.extend(b)             | 列表b接到a后面，相当于a[len(a):] = b|
|a.insert(0,5)           | 在位置0处添上5|
|a[0:3]                  | 返回[0,3)的切片副本,省却即为首尾|
|del a[0]                | 删除a[0]|
|a.pop(2)                | 弹出a[2]并返回，默认a[-1]|
|a.remove(3)             | 弹出第一个值为3的元素|
|a.reverse()             | 逆序|
|a.clear()               | 删除所有元素|
|a.index(x)              | 返回第一个值为x的索引|
|a.count(x)              | 返回x出现的次数|
|a.sort(reverse=True)    | 字典序排序，默认升序|
|a.copy()                | 返回一个浅拷贝|
|min(a)/max/sum          | 返回最小值/最大值/总和|
|*a                      | 解包列表，返回所有元素|
|a+b          | 简单拼接|
|a = [x**3 for x in range(5)]	|列表推导式|


### 3.3 元组

|a = (1,2,3,'233')|list可修改，tuple不可修改|
|---|---|
|a+b                     | 元组简单拼接|
|a = (1,)                | 一个元素后加逗号，否则认为是int型|
|*a						|解包元组|


### 3.4 集合

|a = {1,2,3,'233'}| 重复元素仅保留一个，升序|
|---|---|
|a = set('Hello')|字符串转成升序去重的字符集合|
|a.clear()                | 清空|
|a - b              	 | a和b的差集|
|a | b              	 | a和b的并集|
|a & b              	 | a和b的交集|
|a ^ b              	 | a和b中不同时存在的元素|
|*a						|解包集合|
|a = {x**3 for x in range(5)}	|集合推导式|

### 3.5 字典（类似map）

|a = {'001':'Jason','002':'Kitty'}|key-value任意类型|
|---|---|
|a[key]=value            | 添加键-值对|
|del a['001']            | 删除键值为'001'的键值对|
|a.items()                 | 返回字典的 key-value 对列表|
|a.keys()                 | 返回key组成的list|
|a.values()               | 返回value组成的list|
|a.clear()                | 清空字典|
|a=dict([('a',1),('b',2)])|从list键值对构建字典|
|a = dict(string1=1,string2=2)       | 直接用键值对构建字典|

## 四、条件，循环与函数

### 4.1 条件控制

* 没有switch-case语法
* **if-elis-else** 示例如下：
```python
if x < 0:
	print(1)
elif x > 0:
	print(2)
else:
	print(3)
```

### 4.2 循环控制

* **continue / break** ：继续下一循环 / 跳出循环
* **pass**：什么都不做
* **else**：可以跟在循环后，循环结束或为假时执行，若循环被break则不执行
* **while** 示例如下：
```python
while True:
	break
```

* **for-in** 示例如下：
```python
a = [x*x for x in range(0, 10)]
for item in a[2 : 7]:
	if item == 3:
		continue
	print(item, end=',')
else:
	pass
```

### 4.3 函数

* 可变参数 **def fun(a, b, *args)**
* 默认参数 **def fun(a = 1)**
* 函数中第一个语句为'''string'''或"""string"""的三引号字符串，表示函数的文档字符串，保存在全局变量**function.__doc__**中，示例如下：
```python
def function(a):
	'''this is a docstring'''
	sum = 0
	for i in a:
		sum += i
	return sum
print(function([1, 2, 3]))
print(function.__doc__)
```

* 函数调用可以指定参数，无视顺序
```python
def function(name, age):
	print('name = ', name)
	print('age = ', age)
function(age = 11, name = 'Joy')
```

* 函数内可引用全局变量，但不可修改，除非使用global关键字
```python
x = "old"
def change():
    global x
    x = "new"
change()
print(x)
```

* lambda arg1, arg2...:expression，用简单的表达式表示一个函数，示例如下：
```python
fun = lambda x, y : x + y
print(fun(2, 3))
```

## 五、输入输出

### 5.1 控制台I/O

* x = input('text')，读取一行，可以添加字符串用于提示
* **print(a, b, c, sep = ' ', end = '\n')**，打印，sep修改printf不同元素间的分隔符，end修改print语句后的结束符
* 利用string.format()方法进行格式化输出：**print('{0:<6d},{1:^5s}，{2:2f}'.format(23,'ab',11.2))**，id省略则按原顺序(居左<,居中^,居右>，默认>)，冒号右边省略则是默认格式。常见用法：**print('This is {0} and {1}’.format('A', 'B'))**

### 5.2 文件

|file object||
|---|---|
|f=open(filename,mode)   | 以mode模式打开文件|
|f.write('233')          | 文件写入，返回写入的字符数|
|f.read(size)            | 读取size个字节的数据，无size则所有内容|
|f.readline()            | 读取一行，返回str|
|f.readlines()           | 读取所有行，返回每一行构成的list|
|f.tell()                | 返回文件对象所处位置|
|f.seek(offset,from)     | 改变f所处位置，offset偏移量，from:开头0,当前1,末尾2（默认0）|
|f.close()               | 关闭文件对象|
|a = b'233'              | 创建byte对象|
|a = byte('233','UTF-8') | 创建byte对象，须指定编码格式，默认 UTF-8|
|a.decode()              | byte对象解码为str|

## 六、类

### 6.1 类的定义和实例化

* 变量和方法名前加2个下划线__即表示是私有的
* 类内部函数第一个参数必须是self
* 类的定义和实例化示例如下：
```python
class myClass:
    x = 233

    __secret = 'secret'  # 以2个下划线开头的名字为private

    def __init__(self, name, age):  # 构造函数
        self.name = name
        self.age = age

    @staticmethod  # 声明为静态函数
    def fun(self):
        return 'Hello'


a = myClass('Joy', 12)
a.data = 1	#数据属性无需声明，第一次使用即被引入
print(a.x, a.data)
del a.data	# 删除对象中某一数据
```

### 6.2 类的继承

* `class newClass(class1, class2...):`支持多继承；
* 派生类可以override基类方法，也可以利用`baseClassName.method(self, arguments)`调用基类方法

```python
class newClass(myClass):
    def __init__(self, name, age, sex, organization):
        super().__init__(name, age)	# 调用基类构造函数
        self.sex = sex
        self.organization = organization

    def fun(self):	# 重写基类方法
        s = myClass.fun(self)	# 调用基类方法
        return s + ' world'


b = newClass('Jason', 21, 'male', 'ORZ')
print(isinstance(b, myClass), issubclass(newClass, myClass))
print(b.fun())
```

### 5.3 Iterator & Generator

* 迭代器用于迭代访问容器中的每一个元素；`it = iter(a)`获取容器的迭代器，`next(it)`获取下一个迭代器；
* 可以在类中定义`__iter__()`方法，返回具有`__next__()`的对象，若该类已定义了该方法则返回self即可。一个例子如下：
```python
class Reverse:
    """逆序迭代一个序列 """
    def __init__(self, data):
        self.data = data
        self.index = len(data)

    def __iter__(self):
        return self

    def __next__(self):
        if self.index == 0:
            raise StopIteration
        self.index -= 1
        return self.data[self.index]


a = Reverse('KingJoy')
for p in a:	# Iterate
    print(p, end='')
```

* 生成器是用于创建迭代器的工具，其形式与函数基本一致（区别在于用yield返回）；
* 生成器函数的执行流程和一个例子如下：

1. 调用生成器函数返回一个生成器；
2. 第一次调用next时才执行生成器函数，遇到yield时挂起，并返回此时yield的参数；
3. 再次调用next时，生成器将从上次挂起的位置继续运行，直到再次遇到yield；
4. 在调用next发现没有元素了则抛出`StopIteration`异常，作为for循环的终止条件。

```python
def Reverse(data):
    """逆序迭代一个序列 """
    for idx in range(len(data) - 1, -1, -1):
        yield data[idx]


for p in Reverse('KingJoy'):
    print(p, end='')
```

