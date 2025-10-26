# 此为更新日志，记录每次更新内容，并以版本号为索引
当前版本号：[1.4.0]
- String（自删除缺陷起）
    ## 添加
        [1.0.0] 添加拷贝构造函数
        [1.0.0] 添加移动构造函数
        [1.0.0] 添加非静态成员at函数
        [1.0.0] 添加非静态成员element函数
        [1.0.0] 添加非静态成员empty函数
        [1.0.0] 添加非静态成员bool操作符重载函数
        [1.0.0] 添加非静态成员函数：restore_cache_mode
            用于恢复动态字符串的状态至缓存模式
        [1.0.0] 添加非静态操作符重载成员函数==(...) |==|
            |==|: 添加参数为(char_t)的operator==重载
            |==|: 添加参数为(const_pointer_t)的operator==重载
        [1.0.0] 添加参数为(char_t)的构造函数
        [1.0.0] 添加非静态成员函数swap
        [1.0.0] 添加非静态成员函数move
        [1.1.0] 添加非静态操作符重载成员函数=(...) |=|
            |=|: 添加参数为(const_pointer_t)的operator=重载
            |=|: 添加参数为(basic_string&)的operator=重载
            |=|: 添加参数为(basic_string&&)的operator=重载
        [1.1.0] 添加非静态操作符重载成员函数+=(...) |+=|
            |+=|: 添加参数为(char_t)的operator+=重载
            |+=|: 添加参数为(const_pointer_t)的operator+=重载
            |+=|: 添加参数为(basic_string&)的operator+=重载
        [1.1.0] 添加非静态操作符重载成员函数+(...) |+|
            |+|: 添加参数为(char_t)的operator+重载
            |+|: 添加参数为(const_pointer_t)的operator+重载
            |+|: 添加参数为(basic_string&)的operator+重载
        [1.1.0] 添加参数为可编译期确认字符串的构造函数
        [1.1.1] 添加wrap并添加char_wrap
        [1.1.1] 添加dast并添加string
        [1.2.0] 添加非静态成员函数is_blank
        [1.2.0] 添加非静态成员函数is_digit
        [1.2.0] 添加非静态成员函数is_lower
        [1.2.0] 添加非静态成员函数is_upper
        [1.2.0] 添加非静态成员函数is_enstr
        [1.3.0] 添加非静态成员函数cut
        [1.3.0] 添加非静态成员函数reverse
        [1.3.0] 添加非静态成员函数trimmed
        [1.3.2] 为char工具的strset添加编译期运算
        [1.3.6] 对char工具的strset的编译期块添加提前返回
        [1.4.0] 添加非静态成员函数lower
        [1.4.0] 添加非静态成员函数upper

    ## 删除
        [1.0.0] 将count成员删除
        [1.0.0] 删除string_core的构造函数
        [1.1.4] 删除沉余的以char_warp为类型的参数的构造函数，但是保留wrap
        [1.1.4] 删除沉余的静态成员函数strcopy
        [1.3.1] 删除operator+=的错误逻辑代码
        [1.3.1] 删除char工具的cpy方法的小块拷贝负优化

    ## 改动
        [1.0.0] 将相对应的构造函数转移至basic_string
        [1.0.0] 增加占位大小为7bit的count于buffer_t结构体内
        [1.0.0] 增加占位大小为1bit的cache于buffer_t结构体内
        [1.0.0] 为resize的参数fill添加默认值
        [1.0.0] 将sub功能函数集成于index函数，并删除非静态成员函数sub
        [1.0.0] 已实现增强模式下的operator=特性
        [1.0.0] 将比较函数的逻辑：先比较第一位字符更改为先比较最后一个字符
        [1.0.0] 更改释放的错误参数
        [1.0.0] 将相对应的非静态操作符重载成员函数转移至basic_string
        [1.0.0] 优化非静态成员函数const_string的性能
        [1.0.0] 优化非静态内部成员函数within_range的性能
        [1.0.0] 更改类的实现定义结构
        [1.0.0] 优化非静态成员函数size的性能
        [1.1.1] 将string的实现分块
        [1.1.1] 将原本的参数类型为char[]的编译期构造函数改为类型为wrap::char_wrap
        [1.1.1] 将string归类至dast
        [1.1.2] 更改非静态成员函数respace的逻辑错误：使用realloc更改为使用allocator重新申请内存
        [1.1.3] 根据文档Future的要求，对resize进行优化
        [1.1.3] 优化非静态成员函数mode_state的性能
        [1.1.3] 优化非静态成员函数end的性能
        [1.1.4] 优化非静态成员函数resize的性能
        [1.1.4] 对char工具的strcopy添加编译期分支预测，支持编译期调用
        [1.1.5] 优化非静态成员函数resize的性能
        [1.1.6] 更新restore_cache_mode的逻辑并优化其性能
        [1.3.0] 对于begin和end的core实现，也自basic调用
        [1.3.2] 优化char工具的strset的性能
        [1.3.2] 更改指定构造函数的错误代码
        [1.3.3] 改动operator+=的逻辑
        [1.3.4] 优化operator=(&&)的可读性
        [1.3.5] 更改operator==(const_pointer_t)的错误逻辑
        [1.4.0] 更改参数为(basic_string&)的构造函数的逻辑错误
        [1.4.0] 更改operator+=(...)的逻辑错误
    
    ## 保留
        [1.1.6] 参数为(size_t, Option)的resize暂不纳入更新列表，因为日后可能会删除它
        [1.4.0] 以注释的行驶保留lower与upper的可读性实现

## Describes更新不记录于此日志中