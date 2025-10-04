# !!! 此为缺陷分支，仅保留缺陷库的功能，如要使用，请使用默认分支

# 此项目为现代CPP库，利用现代C++（C++17起包含之前）语法特性实现，为学子们提供现代C++样本。

## 正在实现String

* 快速了解这个项目
    - 项目接文：[ClassInterface]
    - 项目协议：[License]
    - 项目更新：[UpdateLog]
    - 项目源码：[Source]
    - 项目文介：[ImplationFile]

## 规划表

> [!TIP]
> 接口调用采用C++26的显示This与模板可变参数
>
> 若不知晓接口如何使用，请阅读：[ClassInterface]

<dl>
    <dt>关于string在no_residue值特性下的特性</dt>
</dl>

- [x] 64位占用字节为24字节（MSVC，且allocator无状态）
- [x] 自动归回缓存模式


<dl>
    <dt>关于string在remain值特性下的特性</dt>
</dl>

- [x] 当数据未变更时使用原数据，当数据变更时使用新数据
- [x] 自动归回缓存模式

## CMake使用教程
*下载*此项目至本地 <br>
! 使用CMake，若你使用GCC，请使用GCC 15及之上版本 <br>
**若未安装CMake，请安装[CMake](https://cmake.org/)，可在控制台输入CMake -V查看版本，侧面知晓CMake是否安装** <br>
**在项目当前目录下使用控制台输入指令：CMake -B "/ML"，此指令用于指定生成目录，而-B命令参数之后的值是指定的目录，值类型为字符串** <br>

该项目当前使用语言：中文以支持MD文件 <br>
This project is currently using Chinese to support MD files.

[ClassInterface]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md
[License]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/License.md
[UpdateLog]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/UpdateLog.md
[Source]: https://github.com/RockingHeart/Modern-Librarys/tree/main/ModernLibrary/Src
[ImplationFile]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ImplationFile.md