# 此为介绍类与其接口的文档

- String
    - 作用：动态存储字符串
        - 接口
            - 返回值类型：string_core 非静态成员函数名：string_core 参数列表：(const_pointer_t str, size_t size)
            - construct(const_pointer_t str, size_t size)
                - 用于构造动态字符串
                    ### 参数str用于传入需存储的字符串<br>参数size用于告知构造函数需存储的字符串大小
                    额外描述：当使用basic_string进行构造时，实际调用string_core构造函数。先构造核心，再构造框架

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
                函数返回类型描述：若string_trait的模板参数为char，begin与end的返回值类型为char*，以此类推
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
                    函数返回类型描述：若string_trait的模板参数为char，此函数的返回值类型为const char*，以此类推
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
                    #### 以上代码str1输出24（缓存阈值大小）<br>以上代码str2输出60（成员堆大小阈值。请注意：当前该阈值使用构造的字符串大小乘以2以计算，此算法待更改）
                    函数返回描述：无
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
            - 返回值类型：reference 运算符重载函数名：operator[] 参数列表：(size_t position)
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
                    返回值类型描述：若string_trait的模板参数为char，此函数的返回值类型为char&，以此类推
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