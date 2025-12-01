# 此文件介绍实现文件

## utility.ixx
为库提供工具而创建的全局命名模块接口单元

## match.ixx
为库提供工具而创建的utility分区模块接口单元 <br>
内部导出（按照重要级别排列）：template<Type> struct match <br>
match为模板结构体类型，内部成员有found与result，为查找结果提供非：obj.find(...) == static_cast<size_t>(-1)形式的结果存储方式

## type_restion.ixx
为库提供工具而创建的utility分区模块接口单元 <br>
内部导出（按照重要级别排列）：template<type> bool is_character_type，template<type> concept character_type，template<type> concept size_type <br>
is_character_type检查类型是否为字符类型 <br>
character_type约束类型为字符类型 <br>
size_type约束类型为长度类型

## character.ixx
为库提供工具而创建的utility分区模块接口单元 <br>
内部导出（按照重要级别排列）：template <character_type CharType, allocator_type AllocType> struct strutil <br>
strutil为string_traits实现了工具类型