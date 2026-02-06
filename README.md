# 此项目为现代CPP库，利用现代C++（C++17起包含之前）语法特性实现。

## 此为Beta版本，致力于更好的实现（注：测试版本可能尚不完整）

* 快速了解这个项目
    - 项目源码：[Source]
    - 项目规范：[DevStandard]
    - 项目名间：[Namespace]
    - 项目协议：[License]
    - 项目欢庆：[Rejoice]
    - 项目能报：[PerformanceReport]
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
    - Vector
        - 未来：[Future-Vector]
    - Utility
        - 文介：[ImplationFile-Utility]

> [!TIP]
> 接口调用采用C++26的显式This与模板可变参数
>
> 若不知晓接口如何使用，请阅读指定文档

<dl>
    <dt>关于string在no_residue值特性下的特性</dt>
</dl>

- [x] 64位占用大小为32字节（MSVC，char类型，且allocator无状态）
- [x] 64位缓存大小为31字节（MSVC，char类型，且allocator无状态）

性能测试代码：

``` C++
int main() {
    auto stime = GetTickCount64();

    {
        for (size_t i = 0; i < 50000; i++) {
            dast::cstring str = "Hello";
            for (size_t j = 0; j < 50000; j++) {
                str += " World";
            }
        }
    }

    auto etime = GetTickCount64();

    std::cout << "Mine: " << (etime - stime) << '\n';

	stime = GetTickCount64();

    {
        
        for (size_t i = 0; i < 50000; i++) {
            std::string str = "Hello";
            for (size_t j = 0; j < 50000; j++) {
                str += " World";
            }
        }
    }

	etime = GetTickCount64();

    std::cout << "Std: " << (etime - stime) << '\n';
	return 0;
}

```

测试结果（取平均值，单位为tick）：
    Mine: 4000
    Std:  6000