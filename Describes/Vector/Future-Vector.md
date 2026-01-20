Vector规划在此雕刻

- deleted
    vector_traits

- class vector_box<vector_traits VectorTraits, std::size_t BufSize>
    - 该类型用于实现vector内部存储
    - VectorTraits用于规范内部类型
    - BufSize用于设定内部缓冲区大小

- class vector_core<vector_box VectorBox>
    - 该类型用于实现内部非开放接口
    - VectorBox用于规范内部存储

- class basic_vector<vector_core VectorCore>
    - 该类型用于实现外部开放接口
    - VectorCore用于规范内部接口调用

- using dast::vector<class ValueType, std::size_t BufSize = 0>
    - 该类型用于对外开放vector
    - ValueType为内部核心存储类型
    - BufSize为内部缓冲区大小，若小于内部设定的值，则该值在内部无效