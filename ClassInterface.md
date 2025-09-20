# 此为介绍类与其接口的文档

- String
    - 作用：动态存储字符串
        - 接口
            - const_string()
                - 用于获取动态字符串
            - max_size()
                - 用于获取当前动态字符串最大存储大小
            - mode_state()
                - 用于获取模式
            - resize(size_t size)
                - 用于重置与更新动态字符串
            - size()
                - 用于获取当前动态字符串存储大小