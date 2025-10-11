# 此为更新日志，记录每次更新内容
- String（自删除缺陷起）
    ## 删除
        将count成员删除
    ## 非静态成函数
        添加拷贝构造函数
        添加移动构造函数
        添加非静态成员at函数
        添加非静态成员element函数
        添加非静态成员empty函数
        添加非静态成员bool操作符重载函数
        添加非静态成员函数：restore_cache_mode
            用于恢复动态字符串的状态至缓存模式
        添加非静态成员==(...)操作符重载函数 (==)
            (==): 添加参数为(char_t)的operator==重载
            (==): 添加参数为(const_pointer_t)的operator==重载
    ## 改动
        将相对应的构造函数转移至basic_string
        并删除string_core的构造函数
        增加占位大小为7bit的count于buffer_t结构体内
        增加占位大小为1bit的cache于buffer_t结构体内
        为resize的参数fill添加默认值
        将sub功能函数集成于index函数，并删除非静态成员函数sub
        添加参数为(char_t)的构造函数

## Describes更新不记录于此日志中