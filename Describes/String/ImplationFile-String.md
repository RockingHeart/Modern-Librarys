# 此为介绍源码文件的实现目的

## string.ixx
为实现string而创建的模块接口单元 <br>
所属dast命名空间 <br>
内部导出（按照重要级别排列）：string，cstring，wstring <br>
string使用CRTP与friends设计编写 <br>

此类文件为string的组合文件：basic_string, string_box, string_core, string_traits