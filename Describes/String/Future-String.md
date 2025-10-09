# 此为即将实现的功能记录，若已实现指定功能，则删除指定功能记录

- 对于增强模式
    - 被增强的operator=(basic_string&& object)
        - 若self为空，且object不为空，则转移object至self
        - 若self不为空，且object为空，则不做任何操作
        - 若self与object皆不为空，则做swap操作