# 此为介绍Filer类与其接口的文档

## 单文件系统接口快照表

| Interfaces | Shoots |
| :---: | :---: |
| construct | [construct] |
| data | [data] |

- Filer

    > filer是模板类
        > 它需要填入字符类型

    - 作用：操作单文件
        - 类型描述：若字符类型为char，path_t为const char*，以此类推
        - 以下为接口：
            ## construct
            - 返回值类型：filer 构造函数名：filer
                - 参数列表：(void)
                - filer(void)
                    - 用于构造空filer <br>
                - 参数列表：(path_t, permission)
                - filer(path_t path, permission permis = permission::read_only)
                     - 用于以permis权限打开path指定的文件（这个函数会先构造空的读取器再使读取器读取内容） <br>
                - 参数列表：(filoader<char_t>&)
                - filer(filoader<char_t>& filoader)
                     - 用于以filoader打开filoader内部指定的文件（这个函数直接构造读取器） <br>

            
            ## data
            - 返回值类型：auto
                - 参数列表：(void)
                - data()
                    - 用于获取读取器所保存指定文件的内容
                    函数强调返回描述：无

[construct]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Filer/ClassInterface-Filer.md#construct
[data]: https://github.com/RockingHeart/Modern-Librarys/blob/main/Describes/Filer/ClassInterface-Filer.md#data