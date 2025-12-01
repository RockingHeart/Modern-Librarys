# 此项目为现代CPP库，利用现代C++（C++17起包含之前）语法特性实现，为学子们提供现代C++样本。

## 正在实现String

* 快速了解这个项目
    - 项目源码：[Source]
    - 项目规范：[DevStandard]
    - 项目名间：[Namespace]
    - 项目协议：[License]
    - 项目欢庆：[Rejoice]
    - String
        - 接文：[ClassInterface-String]
        - 未来：[Future-String]
        - 更新：[UpdateLog-String]
        - 文介：[ImplationFile-String]
        - 基础：[Base-String]
    - FixedVector
        - 接文：[ClassInterface-FixedVector]
        - 未来：[Future-FixedVector]
        - 更新：[UpdateLog-FixedVector]
        - 文介：[ImplationFile-FixedVector]
    - Utility
        - 文介绍：[ImplationFile-Utility]

## 状态表
> *状态随时更新*

| 项目实现 | 实现状态 | 实现时间 | 版本号 |
| :---: | :---: | :---: | :---: |
| string | 已实现 | 实现基础有效时间为2025年11月份之前 | 1.9.2 |
| fixed_vector | 已实现 | 将于2025年11月份开始实现 | 1.0.0 |
| vector | 待实现 | 将于2026元旦前夕开始实现 | 0.0.0 |

> [!TIP]
> 接口调用采用C++26的显式This与模板可变参数
>
> 若不知晓接口如何使用，请阅读指定文档

<dl>
    <dt>关于string在no_residue值特性下的特性</dt>
</dl>

- [x] 64位占用大小为24字节（MSVC，char类型，且allocator无状态）
- [x] 64位缓存大小为23字节（MSVC，char类型，且allocator无状态）


<dl>
    <dt>关于string在remain值特性下的特性</dt>
</dl>

- [x] 双重数据
- [x] 64位占用大小为48字节（MSVC，char类型，且allocator无状态）
- [x] 64位缓存大小为47字节（MSVC，char类型，且allocator无状态）

## CMake使用教程
*下载*此项目至本地 <br>
! 目前暂不支持跨平台
**若未安装CMake，请安装[CMake](https://cmake.org/)，可在控制台输入CMake -V查看版本，侧面知晓CMake是否安装** <br>
**在项目当前目录下使用控制台输入指令：CMake -B "/ML"，此指令用于指定生成目录，而-B命令参数之后的值是指定的目录，值类型为字符串** <br>

## Q&A
### Q: 关于String，为什么接口是core，basic是核心实现，而basic又实现构造函数、析构函数、运算符？
### A: 此String利用CRTP与显示this以实现接口与实现的分离及独立实现，而在CRTP接口类中，接口内部实现实际使用显示this调用父类的实现，若父类的实现需传入自身类型，那么需在CRTP接口中对this进行转换，会引入转换运行时开销，导致本末倒置，结合其基础由我实现，核心可不由我实现的思想，这是一个深远且正确的选择。

该项目当前使用语言：中文以支持MD文件 <br>
This project is currently using Chinese to support MD files.

[Source]: https://github.com/RockingHeart/Modern-Librarys/tree/main/ModernLibrary/Src
[DevStandard]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/DevStandard.md
[Namespace]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Namespace.md
[License]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/License.md
[Rejoice]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Rejoice.md

[ClassInterface-String]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/String/ClassInterface-String.md
[Future-String]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/String/Future-String.md
[UpdateLog-String]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/String/UpdateLog-String.md
[ImplationFile-String]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/String/ImplationFile-String.md
[Base-String]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/String/Base-String.md

[ClassInterface-FixedVector]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/FixedVector/ClassInterface-FixedVector.md
[Future-FixedVector]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/FixedVector/Future-FixedVector.md
[UpdateLog-FixedVector]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/FixedVector/UpdateLog-FixedVector.md
[ImplationFile-FixedVector]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/FixedVector/ImplationFile-FixedVector.md

[ImplationFile-Utility]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Utility/ImplationFile.md