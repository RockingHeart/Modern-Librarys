# 此项目为现代CPP库，利用现代C++（C++17起包含之前）语法特性实现，为学子们提供现代C++样本。

## 正在实现String

* 快速了解这个项目
    - 项目接文：[ClassInterface]
    - 项目协议：[License]
    - 项目更新：[UpdateLog]
    - 项目源码：[Source]
    - 项目文介：[ImplationFile]

## 规划表
> *实现状态随时更新*

| 项目实现 | 实现状态 | 实现时间 |
| :---: | :---: | :---: |
| string | 正在实现 | 实现基础有效时间为2025年11月份之前 |
| small_vector | 待实现 | 待String实现完毕 |
| vector | 待实现 | 待small_vector实现完毕 |

> [!TIP]
> 接口调用采用C++26的显示This与模板可变参数
>
> 若不知晓接口如何使用，请阅读：[ClassInterface]

<dl>
    <dt>关于string在no_residue值特性下的特性</dt>
</dl>

- [x] 64位占用字节为24字节（MSVC，且allocator无状态）
- [x] 64位的缓存大小为23字节（MSVC，且allocator无状态）


<dl>
    <dt>关于string在remain值特性下的特性</dt>
</dl>

- [x] 双重数据
- [x] 64位占用字节为48字节（MSVC，且allocator无状态）
- [x] 64位的缓存大小为47字节（MSVC，且allocator无状态）

## CMake使用教程
*下载*此项目至本地 <br>
! 使用CMake，若你使用GCC，请使用GCC 15及之上版本 <br>
**若未安装CMake，请安装[CMake](https://cmake.org/)，可在控制台输入CMake -V查看版本，侧面知晓CMake是否安装** <br>
**在项目当前目录下使用控制台输入指令：CMake -B "/ML"，此指令用于指定生成目录，而-B命令参数之后的值是指定的目录，值类型为字符串** <br>

## 对实现基础basic_string的要求
> *实现状态随时更新*

    -若是多个参数的重载，则其参数为(...) <br>
    -模板实现在其名前添加template与其参数 <br>
    -重载实现若有模板重载实现，并不会于其实现表内的名前添加template <br>
    -实现数量有重载实现累加而计

### 构造函数的实现
1. 空构造函数（已实现）
2. 参数为(char_t, size_t)的构造函数（已实现）
3. 参数为(const_pointer_t)的构造函数（已实现）
4. 参数为(const_pointer_t, size_t)的构造函数（已实现）
5. 参数为(const basic_string&)的构造函数（已实现）
6. 参数为(basic_string&&)的构造函数（已实现）<br>
    已实现数量：5

### 运算符重载函数的实现
1. 参数
    1. (const_pointer_t)
    2. (const basic_string&)
    3. (basic_string&&)
2. 以下实现均要求实现其参数为1-3的函数
    1. operator =（未实现）
    2. operator ==（未实现）
    3. operator +（未实现）
    4. operator +=（未实现）
3. operator[] (size_t)（已实现）
4. operator& (void)（未实现）
5. operator| (...)（未实现一个重载）<br>
    已实现数量：1

### 非静态成员函数的实现
 1. begin(void)（已实现）
 2. end(void)（已实现）
 3. const_string(void)（已实现）
 4. tick(...)（已实现一个重载）
 5. disconnect(...)（已实现一个重载）
 6. max_size(void)（已实现）
 7. size(void)（已实现）
 8. resize(size)（已实现）
 9. at(size_t)（未实现）
10. index(...)（已实现两个重载）
11. template<class Type> Type to(...)（已实现一个重载）<br>
    已实现数量：9

该项目当前使用语言：中文以支持MD文件 <br>
This project is currently using Chinese to support MD files.

[ClassInterface]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md
[License]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/License.md
[UpdateLog]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/UpdateLog.md
[Source]: https://github.com/RockingHeart/Modern-Librarys/tree/main/ModernLibrary/Src
[ImplationFile]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ImplationFile.md