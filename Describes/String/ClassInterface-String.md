# 此为介绍类与其接口的文档

## 字符串接口快照表

| Interfaces | Shoots |
| :---: | :---: |
| construct | [construct] |
| begin and end | [begin_and_end] |
| index | [index] |
| clear residue | [clear_residue] |
| leave residue | [leave_residue] |
| const string | [const_string] |
| disconnect | [disconnect] |
| max size | [max_size] |
| mode state | [mode_state] |
| operator | [operator] |
| replace | [replace] |
| residue | [residue] |
| resize | [resize] |
| restore cache mode | [restore_cache_mode] |
| size | [size] |
| tick | [tick] |
| to | [to] |

- String

    > basic_string是模板类
    >    - 它需要填入string_traits
    >        - string_traits需要满足string_traits_type约束

    > string_trait是模板类
    >    - 它需要填入char_t与value_traits

    > value_traits是类枚举
    >    - no_residue
    >    - remain

    - 作用：动态存储字符串
        - 类型描述：若string_trait的模板参数为char，则char_t为char，reference为char&，pointer_t为char*，const_pointer_t为const char*，以此类推
        - 以下为接口：
            ## basic_string
            - 返回值类型：basic_string 构造函数名：basic_string
                - 参数列表：(void)
                - basic_string(void)
                    - 用于构造空状态动态字符串 <br>
                - 参数列表：(const_pointer_t)
                - basic_string(const_pointer_t str)
                    - 用于构造具有str的动态字符串 <br>
                        **参数str用于传入需存储的字符串，自动获取其字符串大小**
                - 参数列表：(const_pointer_t, size_t)
                - basic_string(const_pointer_t str, size_t size)
                    - 用于构造具有size偏移str的动态字符串 <br>
                        **参数str用于传入需存储的字符串 <br> 参数size用于告知构造函数需存储的字符串大小**
            - 模板：template<size_type SizeType> 返回值类型：basic_string basic_string 参数列表：(SizeType, char_t)
            - template<size_type SizeType> basic_string(char_t char_value, SizeType size)
                - 用于构造多个单个字符的动态字符串 <br>
                    **参数size用于传入此方法构造需要的长度**
            - 参数列表：(const basic_string&)
            - basic_string(const basic_string& object)
                - 用于构造与object相同的动态字符串副本 <br>
            - 参数列表：(basic_string&&)
            - basic_string(basic_string&& object)
                - 用于构造转移从object的所有权 <br>
            - 参数列表：(char_t)
            - basic_string(char_t char_value)
                - 用于构造以单个字符串char_value为内容的动态字符串 <br>
                
            ## at
            - 返回值类型：reference_t 非静态成员函数名：at
                - 参数列表：(size_t)
                - reference_t at(size_t position)
                    - 用于获取指定位置的字符
                        - 若position超出正常范围，则抛出错误。若抛出错误，其需捕获类型为const char*
                    ``` C++
                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                        std::cout << str.at(0) << '\n';
                        return 0;
                    }
                    ```
                    #### 以上代码输出：'H'
                    函数返回描述：无

            
            ## begin and end
            - 返回值类型：pointer_t 非静态成员函数名：begin 参数列表：(void) 与 返回值类型：pointer_t 非静态成员函数名：end 参数列表：（void）
            - pointer_t begin(void) 与 pointer_t end(void)
                - begin与end用于支持范围for
                ``` C++
                int main() {
                    basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                    for (auto& c : str) {
                        std::cout << c << ' ';
                    } std::cout << '\n';
                    return 0;
                }
                ```
                #### 以上代码输出："H e l l o"
                函数返回描述：无

            ## index
            - 非静态成员函数名：index
                - 返回值类型：match<size_t> 
                - 参数列表：(char_t, size_t, size_t)
                - match<size_t> index(char_t target, size_t point, size_t end)
                    - 用于查找指定目标的索引
                        - 当参数point大于end时，反向查找
                        - 当参数point小于end时，正向查找
                    ``` C++
                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                        std::cout << str.index('e', 0, str.size()) << '\n';
                        std::cout << str.index('l', str.size(), 0) << '\n';
                        return 0;
                    }
                    ```
                    #### 以上代码第一次输出：1
                    #### 以上代码第二次输出：3
                    函数返回值描述：其返回值类型为模板结构体：template <ResultType> match，有成员为bool类型的found与Result类型的result，found存储查询成功结果，result存储查询结果。
                
                - 返回值类型：bool
                - 参数列表：(size_t)
                - bool index(size_t position)
                - 用于判断position处于合法下标范围
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                        std::cout << str.index(4) << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出： true
                    函数返回值描述：合法则返回true，否则返回false

                    
            
            ## clear_residue
            - 返回值类型：bool 非静态成员函数名：clear_residue 参数列表：(void)
            - bool clear_residue(void)
                - 用于清除保留数据
                    - 它会在清除之前预先检查是否存有保留数据
                    - 检查未存有保留数据则该函数调用失败
                    - 检查存有保留数据并清除保留数据之后返回true
                ``` C++
                int main() {
                    basic_string<string_traits<char, value_traits::remain>> str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
                    str.resize(60);
                    std::cout << str.clear_residue() << '\n';
                    return 0;
                }
                ```
                #### 以上代码输出：'1'

            ## leave_residue
            - 返回值类型：bool 非静态成员函数名：leave_residue 参数列表：(void)
            - bool leave_residue(void)
                - 用于检查是否存有保留数据
                    - 以下条件均满足则存有保留数据，返回true
                        - 是大模式
                        - 记录保留数据的成员数据非空
                ``` C++
                int main() {
                    basic_string<string_traits<char, value_traits::remain>> str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
                    str.resize(60);
                    std::cout << str.leave_residue() << '\n';
                    return 0;
                }
                ```
                #### 以上代码输出：'1'

            ## const_string
            - 返回值类型：const_pointer_t 非静态成员函数名：const_string 参数列表：(void)
            - const_pointer_t const_string(void)
                - 用于获取动态字符串
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                        std::cout << str.const_string() << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出："Hello"
                    函数返回描述：无

            ## disconnect
            - 返回值类型：basic_string 非静态成员函数名：disconnect
                - 参数列表：(size_t, size_t)
                - basic_string disconnect(size_t point, size_t end)
                    - 用于截取字符串区间的字符串 <br>
                    **参数point为截取的起始位置 <br> 参数end为截取的终止位置**
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                        std::cout << str.disconnect(1, 4).const_string() << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出："ell"
                    函数返回值描述：返回截取后的字符串

            
            ## max_size
            - 返回值类型：size_t 非静态成员函数名：max_size 参数列表：(void)
            - size_t max_size(void)
                - 用于获取当前动态字符串最大存储大小
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str1 = { "Hello", 5 };
                        std::cout << str.max_size() << '\n'

                        basic_string<string_traits<char, value_traits::remain>> str2 = { "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 30 };
                        std::cout << str.max_size() << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码str1输出24（缓存阈值大小）<br> 以上代码str2输出60（成员堆大小阈值。请注意：当前该阈值使用构造的字符串大小乘以2以计算，此算法待更改）
                    函数返回描述：无
            
            ## mode_state
            - 返回值类型：mode_status 非静态成员函数名：mode_state 参数列表：(void)
            - mode_status mode_state(void)
                - 用于获取模式
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str1 = { "Hello", 5 };
                        std::cout << str.mode_state() << '\n'

                        basic_string<string_traits<char, value_traits::remain>> str2 = { "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 30 };
                        std::cout << str.mode_state() << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码str1输出： 0（缓存模式）<br>以上代码str2输出：1（大模式）
                    函数返回值类型描述：mode_status是枚举类型，内部有cache与big两种值，对应缓存模式与大模式。

            ## operator+=
            - 返回值类型：basic_string& 非静态成员运算符重载函数符号：+=
                - 参数列表：(char_t)
                - basic_string& operator+=(char_t char_value)
                    - 用于扩展动态字符串
                        ``` C++
                        import string;
                        import std;

                        int main() {
                            basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                            str += 'A';
                            std::cout << str.const_string() << '\n'
                            return 0;
                        }
                        ```
                        #### 以上代码输出："HelloA"
                        函数返回值描述：返回调用operator+=的对象
            
            ## operator[]
            - 返回值类型：reference 非静态成员运算符重载函数符号：[]
                - 参数列表：(size_t)
                - reference operator[](size_t position)
                    - 用于获取指定位置的字符，而非字符串
                        ``` C++
                        import string;
                        import std;

                        int main() {
                            basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                            std::cout << str[0] << '\n'
                            return 0;
                        }
                        ```
                        #### 以上代码输出：'H'
                        函数返回描述：无
            
            ## operator==
            - 返回值类型：bool 非静态成员运算符重载函数符号：[]==
                - 参数类型：(char_t)
                - bool operator==(char_t char_value)
                    - 用于比较存储的内容是否等于char_value
                         ``` C++
                        import string;
                        import std;

                        int main() {
                            basic_string<string_traits<char, value_traits::remain>> str = { "A", 1 };
                            std::cout << (str == 'A') << '\n'
                            return 0;
                        }
                        ```
                        #### 以上代码输出：1
                        函数返回描述：无
                
                - 参数类型：(const_pointer_t)
                - bool operator==(const_pointer_t str)
                    - 用于比较存储的内容是否等于str
                         ``` C++
                        import string;
                        import std;

                        int main() {
                            basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 1 };
                            std::cout << (str == "Hello") << '\n'
                            return 0;
                        }
                        ```
                        #### 以上代码输出：1
                        函数返回描述：无

            ## replace
            - 返回值类型：bool 非静态成员函数名：replace
            - 用于重置指定位置的动态字符串
                - 参数列表：(const_pointer_t, size_t, size_t)
                - bool replace(const_pointer_t str, size_t point, size_t end) <br>
                    **参数str为待替换的字符串 <br> 参数point为指定位置的起始位置 <br> 参数end为指定位置的终止位置**
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                        str.replace("World", 0, 5);
                        std::cout << str.const_string() << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出："World"
                    函数返回值描述：此函数返回bool值，指告用户replace成功与否

                - 参数列表：(reference, size_t, size_t)
                - bool replace(reference char_value, size_t point, size_t end)<br>
                    **参数char_value为待替换的单个字符 <br> 参数point为指定位置的起始位置 <br> 参数end为指定位置的终止位置**
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                        str.replace('A', 0, 5);
                        std::cout << str.const_string() << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出：49
                    注：保留数据仅当remain特性实例化的basic_string变量满足以下条件时保留
                        - 变量是大模式
                        - 调用resize更新变量为更大的动态字符串
                    函数返回值描述：若存有保留数据，则返回其保留数据
            
            ## residue
            - 返回值类型：const residue_info 非静态成员函数名：residue 参数列表：(void)
            - const residue_info residue(void)
                - 用于获取保留数据
                ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
                        str.resize(60);
                        if (str.leave_residue()) {
	                        std::cout << str.residue().size << '\n';
                        }
                        return 0;
                    }
                ```
                #### 以上代码输出："AAAAA"
                函数返回值描述：此函数返回bool值，指告用户replace成功与否

            ## resize
            - 返回值类型：bool 非静态成员函数名：resize 参数列表：(size_t, char_t)
            - bool resize(size_t size, char_t fill)
                - 用于重置与更新动态字符串<br>
                    **参数size用于控制重置的大小**
                    **参数fill用于填充扩展**
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str1 = { "Hello", 5 };

                        auto print_str = [&]() {
                            std::cout << str.const_string() << ' '
                            std::cout << static_cast<size_t>(str.mode_state()) << ' '
                            std::cout << str.max_size() << '\n'
                        };

                        str.resize(12);
                        print_str();

                        str.resize(30);
                        print_str();
                        return 0;
                    }
                    ```
                    #### 以上代码第一次输出："Hello" 0 24<br>以上代码第二次输出："Hello" 1 30
                    函数返回值描述：此函数返回bool值，指告用户resize成功与否

            ## restore_cache_mode
            - 返回值类型：bool 非静态成员函数名：restore_cache_mode
                - 参数列表：(void)
                - bool restore_cache_mode(void)
                    - 用于恢复至缓存模式
                        - 此无参重载将自动计算恢复长度
                            - 若自动计算失败，其默认长度为1
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str1 = { 'A', 50 };
                        str[0] = ':';
                        str1.resize(30);
                        str.restore_cache_mode();
                        std::cout << str.const_string() << '\n';
                        return 0;
                    }
                    ```
                    #### 以上代码输出：":AAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                    函数返回值描述：恢复成功则返回true，反之回false
                    
                - 参数列表：(size_t)
                - bool restore_cache_mode(size_t size)
                    - 用于恢复至缓存模式
                        - 调用此size_t重载，若成功，缓存大小设定为size
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str1 = { 'A', 50 };
                        str.restore_cache_mode(12);
                        std::cout << str.const_string() << '\n';
                        return 0;
                    }
                    ```
                     #### 以上代码输出："AAAAAAAAAAAA"
                    函数返回值描述：恢复成功则返回true，反之回false

            ## size
            - 返回值类型：size_t 非静态成员函数名：size 参数列表：(void)
            - size_t size(void)
                - 用于获取当前动态字符串存储大小
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                        std::cout << str.size() << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出： 5
                    函数返回描述：无

            ## tick
            - 返回值类型：size_t 非静态成员函数名：tick
                - 参数列表: (char_t, size_t, size_t)
                - size_t tick(char_t char_value, size_t point, size_t end)
                    - 用于计数字符串内的char_value <br>
                    **参数char_value为查找的目标 <br> 参数point为查找的起始位置 <br> 参数end为查找的终止位置**
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                        std::cout << str.tick('l', 0, str.size()) << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出：2
                    函数返回值描述：返回查找的计数结果

            ## to
            - 模板参数：<CastType> 返回值类型：CastType 非静态模板成员函数名：to
                - 参数列表: (void)
                - CastType to(void)
                    - 用于将动态字符串对象转换为CastType类型对象
                    - 需要填入模板参数
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                        std::string std_str = str.to<std::string>();
                        std::cout << std_str << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出： "Hello"
                    函数返回值描述：它由CastType所构造
                
                - 参数列表：(size_t)
                - CastType to(size_t offset)
                    - 用于将动态字符串对象偏移offset数目的字符串转换为CastType类型对象
                    - 需要填入模板参数
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        basic_string<string_traits<char, value_traits::remain>> str = { "Hello", 5 };
                        std::string std_str = str.to<std::string>(1);
                        std::cout << std_str << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出： "ello"
                    函数返回值描述：它由CastType所构造

[construct]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#at
[construct]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#basic_string
[begin_and_end]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#begin-and-end
[index]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#index
[clear_residue]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#clear_residue
[leave_residue]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#leave_residue
[const_string]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#const_string
[disconnect]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#disconnect
[max_size]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#max_size
[mode_state]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#mode_state
[operator]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#operator
[replace]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#replace
[residue]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#residue
[resize]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#resize
[restore_cache_mode]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#restore_cache_mode
[size]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#size
[tick]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#tick
[to]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/ClassInterface.md#to