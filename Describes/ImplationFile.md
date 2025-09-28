# 此为介绍源码文件的实现目的

## string.ixx
为实现basic_string而创建的模块接口单元 <br>
内部导出（按照重要级别排列）：basic_string, string_traits, value_traits <br>
basic_string使用CRTP与friends设计编写 <br>
当使用basic_string进行构造时，实际调用string_core构造函数：先构造核心，再构造框架。核心由实现构建 <br>

## utility.ixx
为库提供工具而创建的全局命名模块接口单元

## match.ixx
为库提供工具而创建的utility分区模块接口单元 <br>
内部导出（按照重要级别排列）：template Type match <br>
match为模板结构体类型，内部成员有found与result，为查找结果提供非：obj.find(...) == static_cast<size_t>(-1)形式的结果存储方式 <br>
当返回值为match时，需要import utility.match