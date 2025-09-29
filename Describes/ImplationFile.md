# 此为介绍源码文件的实现目的

## string.ixx
为实现basic_string而创建的模块接口单元 <br>
内部导出（按照重要级别排列）：basic_string, string_traits, value_traits <br>
basic_string使用CRTP与friends设计编写 <br>
当使用basic_string进行构造时，实际调用string_core构造函数：先构造核心，再构造框架。核心由实现构建 <br>
该动态字符串实现适用于两极端场景：节省空间与双倍数据，它并非为极致性能而设计。no_residue（节省空间）模式且为MSVC编译器，basic_string占用24字节；remain（双从数据）模式下，basic_string处于大模式且有保留，则可操控保留数据，当数据未变更时使用原数据，当数据变更时使用新数据

## utility.ixx
为库提供工具而创建的全局命名模块接口单元

## match.ixx
为库提供工具而创建的utility分区模块接口单元 <br>
内部导出（按照重要级别排列）：template Type match <br>
match为模板结构体类型，内部成员有found与result，为查找结果提供非：obj.find(...) == static_cast<size_t>(-1)形式的结果存储方式 <br>
当返回值为match时，需要import utility.match