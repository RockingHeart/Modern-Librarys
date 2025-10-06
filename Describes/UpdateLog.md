# 此为更新日志，记录每次更新内容
- String（自删除缺陷起）
    - 将count成员删除
    - 添加占位大小为7bit的count于buffer_t结构体内
    - 添加占位大小为1bit的cache于buffer_t结构体内
    - 为resize的参数fill添加默认值
    - 将sub功能函数集成于index函数，并删除非静态成员函数sub
    - 添加非静态成员函数：restore_cache_mode
        - 用于恢复动态字符串的状态至缓存模式
    - 添加拷贝构造函数
    - 添加移动构造函数

## Describes更新不记录于此日志中