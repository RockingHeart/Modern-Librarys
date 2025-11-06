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
    1. operator =（已实现完基础要求的重载）
    3. operator +=（已实现完基础要求的重载）
3. operator +(...)（已实现三个重载）
4. operator ==(...)（已实现两个重载）
5. operator[] (size_t)（已实现）<br>
    已实现数量：18

### 非静态成员函数的实现
 1. begin(void)（已实现）
 2. end(void)（已实现）
 3. const_string(void)（已实现）
 4. tick(...)（已实现一个重载）
 5. disconnect(...)（已实现一个重载）
 6. max_size(void)（已实现）
 7. size(void)（已实现）
 8. resize(size)（已实现）
 9. at(size_t)（已实现）
10. index(...)（已实现两个重载）
11. template<class Type> Type to(...)（已实现一个重载）<br>
    已实现数量：12