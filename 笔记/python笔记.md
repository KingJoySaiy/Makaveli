## 一、操作符 operator
```table
常用操作符
a ** b                  | a的b次方
pow(a,b)                | a的b次方
a // b                  | 除法并向下取整
a + b                   | 算术加,str,list,tuple中为拼接
a - b                   | 算术减,set中为差集
a丨b                    | 逻辑或,set中为并集
a & b                   | 逻辑与,set中为交集
a ^ b                   | 逻辑异或,set中为对称差
abs(a)                  | 取绝对值
complex(i,j)            | 返回实虚部分别为i,j的复数
a.conjugate()           | 返回复数的共轭复数
divmod(x,y)             | 返回数值对(x//y,x%y),结果和余数
a is (not) b            | 判断是否引用同一个对象
and / or / not          | 与或非
x<<1 / x>>1             | 左移/右移
~x                      | 按位取反
a**=b                   | 幂赋值
a//=b                   | 取整除法赋值
a,b = x,y               | 对应赋值a=x,b=y
```

```table
关键字
pass                    | 跳过不执行操作
def 函数名(参数列表)      | 定义函数
global a                | 局部作用域中使用全局变量 
sep=' '                 | 控制分隔符，默认空格
end='\n'                | 控制结束符，默认换行
import                  | 导入模块
from collections import deque | 从模块中导入模块
with open('233.txt') as file_object:  | 打开文件并定义文件对象名为file_object
form time import *      | 导入模块中的所有函数或变量名称
import math as x        | 导入模块并重命名
int()                   | str强制转换为int
float()                 | str强制转换为float

```

## 二、方法 method
```table
import package
keywords                | 提供标准库关键字
math                    | 提供数学库
platform                | 获得操作系统,系统架构,python信息等
time                    | 获取当前时间
builtins                | 内建名称空间(提供不用导入就能调用的内建函数)
collections             | 容器库
unittest                | 提供代码测试工具,测试函数是否在各种情形下的行为都符合要求
```

```table
常用方法
keywords.kwlist         | 输出标准库的所有关键字
'233' (not) in a        | 判断'233'是否在a中，返回布尔值
type(a)                 | 返回变量a的对象类型
len(a)                  | 返回元素个数
sorted(a,reverse=True)  | 默认升序排序
input(x)                | 输出x，并读取下一个字符串
range(s,e,step)         | [s,e)中步长为step的range对象
id(a)                   | 返回a的地址
dir(list)               | 查询类的所有属性，查询模块定义的所有名字
help(list)              | 查询说明文档
```

## 二、字符串 str
```table
a = '233' / "233" 皆可
a.upper()               | 转为大写
a.lower()               | 转为小写
a.title()               | 所有单词以大写开始，其余小写
a.rjust(len,char)       | 长度扩展为len,原字符在右侧，其余填充char(默认空格)
a.ljust(len,char)       | 同上，原字符在左侧
a='{id1:<6d},{id2:^5d}'.format(23,13) | 字符串格式化，id省略则按原顺序(居左<,居中^,居右>，默认>)
```

## 三、列表 List
```table
a = [1,2,3]
a.append(4)             | 末尾添上4
a.extend(b)             | 列表b接到a后面
a.insert(0,5)           | 在位置0处添上5
a[0:3]                  | 返回[0,3)的切片副本,省却即为首尾
del a[0]                | 删除a[0]
a.pop(2)                | 弹出a[2]并返回，默认a[-1]
a.remove(3)             | 弹出值为3的元素
a.reverse()             | 逆序
a.clear()               | 删除所有元素
a.index(x)              | 返回第一个值为x的索引
a.count(x)              | 返回x出现的次数
a.sort(reverse=True)    | 字典序排序，默认升序
a.copy()                | 返回一个浅拷贝
min(a)/max/sum          | 返回最小值/最大值/总和
*a                      | 解包列表，返回所有元素
```

```table
其他 
range(1,10,3)           | 生成[1,10)内间隔为3的数字
list(range(4))          | 将[0,4)转化为列表
b = (1,4,2,3)           | 小括号为不可变的元组
```

## 四、元组 tuple
与 list 类似，但是tuple元素不能修改
```table
a = (1,2,3,'233') 
a+b                     | 元组简单拼接
a = (1,)                | 一个元素后加逗号，否则认为是int型
```

## 五、集合 set
```table
a = {1,2,3,'233'}
a = set('123abc')       | 字符串拆分成字符集合
a = set()               | 创建空集合
```

## 六、字典 dict
```table
a = {'001':'Jason','002':'Kitty'}|key-value任意类型
a = {}                  | 创建空字典
a[key]=value            | 添加键-值对
del a['001']            | 删除键值为'001'的键值对
.item()                 | 返回字典的 key-value 对列表
.keys()                 | 返回key组成的list
.values()               | 返回value组成的list
.clear()                | 清空字典
a=dict([('a',1),('b',2)])|从list键值对构建字典
a = dict(a=1,b=2)       | 直接用键值对构建字典
**a                     | 
```

## 七、文件 file
```table
file object
f=open(filename,mode)   | 以mode模式打开文件
f.write('233')          | 文件写入，返回写入的字符数
f.read(size)            | 读取size个字节的数据，无size则所有内容
f.readline()            | 读取一行，返回str
f.readlines()           | 读取所有行，返回每一行构成的list
f.tell()                | 返回文件对象所处位置
f.seek(offset,from)     | 改变f所处位置，offset偏移量，from:开头0,当前1,末尾2（默认0）
f.close()               | 关闭文件对象
a = b'233'              | 创建byte对象
a = byte('233','UTF-8') | 创建byte对象，须指定编码格式，默认 UTF-8
a.decode()              | byte对象解码为str

```



