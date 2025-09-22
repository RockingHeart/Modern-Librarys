# 此为介绍类与其接口的文档

- String
    - 作用：动态存储字符串
        - 类型描述：若string_trait的模板参数为char，则值类型为char，引用类型为char&，指针类型为char*，以此类推
        - 对构造函数额外描述：当使用basic_string进行构造时，实际调用string_core构造函数。先构造核心，再构造框架
        - 接口
            ## string_core
            - 返回值类型：string_core 构造函数名：string_core
                - 参数列表：(const_pointer_t str)
                - string_core(const_pointer_t str)
                    - 用于构造动态字符串
                        ### 参数str用于传入需存储的字符串，自动获取其字符串大小
                - 参数列表：(const_pointer_t str, size_t size)
                - string_core(const_pointer_t str, size_t size)
                    - 用于构造动态字符串
                        ### 参数str用于传入需存储的字符串<br>参数size用于告知构造函数需存储的字符串大小
            - 模板：template<size_type SizeType> 返回值类型：string_core 构造函数名：string_core 参数列表：(SizeType size, char_t char_value)
            - template<size_type SizeType> string_core(SizeType size, char_t char_value)
                - 用于构造多个单个字符的动态字符串
                    ### 参数size用于传入此方法构造需要的长度
            
            ## begin and end
            - 返回值类型：pointer_t 非静态成员函数名：begin 参数列表：(void) 与 返回值类型：pointer_t 非静态成员函数名：end 参数列表：（void）
            - pointer_t begin(void) 与 pointer_t end(void)
                - begin与end用于支持范围for
                ``` C++
                int main() {
                    string<string_trait<char>> str = { "Hello", 5 };
                    for (auto& c : str) {
                        std::cout << c << ' ';
                    } std::cout << '\n';
                    return 0;
                }
                ```
                #### 以上代码输出："H e l l o"
                函数返回描述：无
            
            ## clear_residue
            - 返回值类型：bool 非静态成员函数名：clear_residue 参数列表：(void)
            - bool clear_residue(void)
                - 用于清除保留数据
                    - 它会在清除之前预先检查是否存有保留数据
                    - 检查未存有保留数据则该函数调用失败
                    - 检查存有保留数据并清除保留数据之后返回true
                ``` C++
                int main() {
                    basic_string<string_traits<char>> str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
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
                    basic_string<string_traits<char>> str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
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
                        string<string_trait<char>> str = { "Hello", 5 };
                        std::cout << str.const_string() << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出："Hello"
                    函数返回描述：无
            
            ## max_size
            - 返回值类型：size_t 非静态成员函数名：max_size 参数列表：(void)
            - size_t max_size(void)
                - 用于获取当前动态字符串最大存储大小
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        string<string_trait<char>> str1 = { "Hello", 5 };
                        std::cout << str.max_size() << '\n'

                        string<string_trait<char>> str2 = { "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 30 };
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
                        string<string_trait<char>> str1 = { "Hello", 5 };
                        std::cout << str.mode_state() << '\n'

                        string<string_trait<char>> str2 = { "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 30 };
                        std::cout << str.mode_state() << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码str1输出： 0（缓存模式）<br>以上代码str2输出：1（大模式）
                    函数返回值类型描述：mode_status是枚举类型，内部有cache与big两种值，对应缓存模式与大模式。
            
            ## operator[]
            - 返回值类型：reference 非静态成员运算符重载函数名：operator[] 参数列表：(size_t position)
            - reference operator[](size_t position)
                - 用于获取指定位置的字符，而非字符串
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        string<string_trait<char>> str = { "Hello", 5 };
                        std::cout << str[0] << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出：'H'
                    函数返回描述：无

            ## replace
            - 返回值类型：bool 非静态成员函数名：replace
            - 用于重置指定位置的动态字符串
                - 参数列表：(const_pointer_t str, size_t point, size_t end)
                - bool replace(const_pointer_t str, size_t point, size_t end)
                    ### 参数str为待替换的字符串 <br> 参数point为指定位置的起始位置 <br> 参数end为指定位置的终止位置
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        string<string_trait<char>> str = { "Hello", 5 };
                        str.replace("World", 0, 5);
                        std::cout << str.const_string() << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码输出："World"
                    函数返回值描述：此函数返回bool值，指告用户replace成功与否

                - 参数列表：(reference char_value, size_t point, size_t end)
                - bool replace(reference char_value, size_t point, size_t end)
                    ### 参数char_value为待替换的单个字符 <br> 参数point为指定位置的起始位置 <br> 参数end为指定位置的终止位置
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        string<string_trait<char>> str = { "Hello", 5 };
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
                        basic_string<string_traits<char>> str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
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
            - 返回值类型：bool 非静态成员函数名：resize 参数列表：(size_t size)
            - bool resize(size_t size)
                - 用于重置与更新动态字符串
                    ### 参数size用于控制重置的大小
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        string<string_trait<char>> str1 = { "Hello", 5 };

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

            ## size
            - 返回值类型：size_t 非静态成员函数名：size 参数列表：(void)
            - size_t size(void)
                - 用于获取当前动态字符串存储大小
                    ``` C++
                    import string;
                    import std;

                    int main() {
                        string<string_trait<char>> str = { "Hello", 5 };
                        std::cout << str.size() << '\n'
                        return 0;
                    }
                    ```
                    #### 以上代码str输出： 5
                    函数返回描述：无