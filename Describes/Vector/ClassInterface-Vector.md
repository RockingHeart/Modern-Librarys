# 此为介绍Vector类与其接口的文档

## 定长向量接口快照表

| Interfaces | Shoots |
| :---: | :---: |
| construct | [construct] |
| push_back | [push_back] |
| pop_back | [pop_back] |
| data_size | [data_size] |
| size | [size] |
| bufsize | [bufsize] |
| begin and end | [begin_and_end] |
| at | [at] |
| operator | [operator] |

- Vector

    > vector是模板类
        > 它需要填入值类型与缓冲区长度
            > 缓冲区长度为0则无缓冲区
            > 若缓冲区长度较小则会调整

    - 作用：静态与动态存储非定长向量元素
        - 类型描述：若值类型为int，则reference为int&，以此类推
        - 以下为接口：
            ## construct
            - 返回值类型：vector 构造函数名：vector
            - 参数列表：(void)
                - vector(void)
                    - 用于构造空状态定长向量 <br>

            ## push_back
            - 返回值类型：void
                - 参数列表：(const value_t& value)
                - push_back(const value_t& value)
                    - 用于将元素推入末尾
                    ``` C++
                    import vector;
                    import std;
                    
                    int main() {
                        dast::vector<int, 6> vec;
                        vec.push_back(0);
                        return 0;
                    }
                    ```
                    函数强调返回描述：无

            ## pop_back
            - 返回值类型：bool
                - 参数列表：(void)
                - pop_back(void)
                    - 用于弹出元素
                    ``` C++
                    import vector;
                    import std;
                    
                    int main() {
                        dast::vector<int, 6> vec;
                        vec.push_back(0);
                        std::cout << vec.pop_back();
                        return 0;
                    }
                    ```
                    #### 以上代码输出： true
                    函数强调返回描述：
                    - 若无元素可弹出则返回false
                    - 若弹出成功则返回true

            ## data_size
            - 返回值类型：size_t
                - 参数类型：(void)
                - data_size(void)
                    - 用于直接地获取数据长度
                    ``` C++
                    import vector;
                    import std;
                    
                    int main() {
                        dast::vector<int, 0> vec;
                        vec.push_back(0);
                        std::cout << vec.data_size();
                        return 0;
                    }
                    ```
                    #### 以上代码输出： 1
                    函数强调返回描述：无

            ## size
            - 返回值类型：size_t
                - 参数类型：(void)
                - size(void)
                    - 用于获取不同模式的数据长度
                    ``` C++
                    import vector;
                    import std;
                    
                    int main() {
                        dast::vector<int, 6> vec;
                        vec.push_back(0);
                        std::cout << vec.size();
                        return 0;
                    }
                    ```
                    #### 以上代码输出： 1
                    函数强调返回描述：无

            ## bufsize
            - 返回值类型：size_t
            - 此为静态函数
                - 参数类型：(void)
                - bufsize(void)
                    - 用于获取真实缓冲区最大长度
                    ``` C++
                    import vector;
                    import std;
                    
                    int main() {
                        dast::vector<int, 6> vec;
                        std::cout << decltype(vec)::bufsize();
                        return 0;
                    }
                    ```
                    #### 以上代码输出： 6
                    函数强调返回描述：无

            ## begin and end
            - 返回值类型：pointer_t 非静态成员函数名：begin 参数列表：(void) 与 返回值类型：pointer_t 非静态成员函数名：end 参数列表：（void）
            - pointer_t begin(void) 与 pointer_t end(void)
                - begin与end用于支持范围for
                ``` C++
                import vector;
                import std;

                int main() {
                    dast::vector<int, 0> vec;
                    for (std::size_t i = 0; i < 5; i++) {
                        vec.push_back(i);
                    }
                    size_t count = 0;
                    for (auto& v : vec) {
                        v = count;
                        count += 1;
                        std::cout << v << ' ';
                    } std::cout << '\n';
                    return 0;
                }
                ```
                #### 以上代码输出：0 1 2 3 4
                函数强调返回描述：无

            ## at
            - 返回值类型：reference_t 非静态成员函数名：at 参数列表：(size_t)
            - reference_t at(size_t size)
                - 用于获取指定位置的元素
                - 当position大于最大容量时，则抛出const char*类型的异常
                    ``` C++
                    import vector;
                    import std;

                    int main() {
                        dast::vector<int, 0> vec;
                        vec.push_back(1);
                        std::cout << vec.at(0) << '\n' // out: 1
                        vec.at(2); // Exception: Out of range
                        return 0;
                    }
                    ```
                    #### 由于抛出异常，以上代码执行至vec.at(2)时终止
                    函数强调返回描述：无

            ## operator
            - operator[]
                - 返回值类型：reference_t 非静态运算符重载符：[] 参数列表：(size_t)
                - reference_t operator[](size_t size)
                    - 用于获取指定位置的元素
                        ``` C++
                        import vector;
                        import std;

                        int main() {
                            dast::vector<int, 0> vec;
                            std::cout << (vec[0] = 1) << '\n'
                            return 0;
                        }
                        ```
                        #### 以上代码输出： 1
                        函数强调返回描述：无
            

[construct]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Vector/ClassInterface-Vector.md#construct
[push_back]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Vector/ClassInterface-Vector.md#push_back
[pop_back]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Vector/ClassInterface-Vector.md#pop_back
[data_size]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Vector/ClassInterface-Vector.md#data_size
[size]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Vector/ClassInterface-Vector.md#size
[bufsize]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Vector/ClassInterface-Vector.md#bufsize
[begin_and_end]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Vector/ClassInterface-Vector.md#begin-and-end
[at]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Vector/ClassInterface-Vector.md#at
[operator]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Vector/ClassInterface-Vector.md#operator